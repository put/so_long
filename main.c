/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:54:47 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/30 00:00:26 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/include/MLX42/MLX42.h"

static void freestrarr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *getsetrawmap(char *newmap, t_bool clear)
{
	static char *rawmap = NULL;

	if (newmap != NULL)
	{
		free(rawmap);
		rawmap = newmap;
	}
	if (clear)
		free(rawmap);
	return (rawmap);
}

char ***getsetmap(char **newmap, t_bool clear)
{
	static char **map = NULL;

	if (newmap != NULL)
	{
		freestrarr(map);
		map = newmap;
	}
	if (clear)
		freestrarr(map);
	return (&map);
}

static t_tile *getplayerloc(char **map)
{
	int x;
	int y;
	t_tile *loc;

	y = 0;
	loc = malloc(sizeof(t_tile));
	if (loc == NULL)
		return (NULL);
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'P')
			{
				*loc = (t_tile){x, y};
				return (loc);
			}
			x++;
		}
		y++;
	}
	return (loc);
}

static void do_movement(t_direction dir)
{
	char **map;
	t_tile *loc;
	t_tile newloc;

	map = *getsetmap(NULL, FALSE);
	loc = getplayerloc(map);
	newloc = (t_tile){loc->x, loc->y};
	printf("loc: %d, %d\n", loc->x, loc->y);
	if (dir == UP)
		newloc.y--;
	if (dir == DOWN)
		newloc.y++;
	if (dir == LEFT)
		newloc.x--;
	if (dir == RIGHT)
		newloc.x++;
	if (map[newloc.y][newloc.x] == '1')
		return;
	if (map[newloc.y][newloc.x] == 'C')
	{
		map[newloc.y][newloc.x] = '0';
	}
	map[loc->y][loc->x] = '0';
	map[newloc.y][newloc.x] = 'P';
}

static void handle_keypress(void *param)
{
	mlx_t *mlx;

	mlx = (mlx_t *)param;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
		do_movement(UP);
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		do_movement(LEFT);
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		do_movement(DOWN);
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		do_movement(RIGHT);
}

static t_imgtype get_tiletype(char c)
{
	if (c == '1')
		return (IMG_WALL);
	if (c == '0')
		return (IMG_FLOOR);
	if (c == 'C')
		return (IMG_FLOOR);
	if (c == 'E')
		return (IMG_EXIT);
	if (c == 'P')
		return (IMG_FLOOR);
	return (IMG_ERROR);
}

void update_game(void* param)
{
	mlx_t *mlx;
	char **map;
	static t_tile *loc = NULL;
	t_tile *newloc;
	
	mlx = (mlx_t *)param;
	map = *getsetmap(NULL, FALSE);
	if (!loc)
	{
		loc = getplayerloc(map);
		draw_map(mlx);
		return;
	}
	//TODO: ^^^^^^get player loc can fail, must init kill game to free shit and error out etcetc
	newloc = getplayerloc(map);
	//TODO: ^^^^^^get player loc can fail, must init kill game to free shit and error out etcetc
	if (loc->x == newloc->x && loc->y == newloc->y)
	{
		free(newloc);
		return;
	}
	map[loc->y][loc->x] = '0';
	map[newloc->y][newloc->x] = 'P';
	free(loc);
	loc = newloc;
	draw_map(mlx);
}

static t_bool floodsuccess(char **map)
{
	int x;
	int y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			printf("%c", map[y][x]);
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (FALSE);
			x++;
		}
		printf("\n");
		y++;
	}
	return (TRUE);
}

static int verifymap(char *rawmap)
{
	int width;
	int height;
	char **map;
	t_tile *playerloc;
	int objectreturn;

	width = getmapwidth(rawmap);
	height = getmapheight(rawmap);
	if (!verifyrect(rawmap, width))
		return (-3);
	map = getsplitmap(rawmap);
	if (!map)
		return (-1);
	if (!verifywalls(map, width))
		return (freestrarr(map), -4);
	objectreturn = verifyobjects(rawmap);
	if (!objectreturn)
		return (freestrarr(map), objectreturn);
	playerloc = getplayerloc(map);
	if (!playerloc || playerloc->x == -1)
		return (freestrarr(map), -5);
	if (!floodsuccess(floodfill(map, playerloc, width, height)))
		return (freestrarr(map), -6);
	return (freestrarr(map), 1);
}

char *getrawmap(char *filename)
{
	char *lastdot;

	lastdot = ft_strrchr(filename, '.');
	if (lastdot == NULL)
		return (NULL);
	if (ft_strncmp(lastdot, ".ber", 4) != 0)
		return (NULL);
	return (readmapfile(filename));
}

void errormsg(char *msg)
{
	ft_printf("Error\n%s\n", msg);
}

char *get_map_err(int err)
{
	if (err == -1)
		return ("Failed to split map");
	if (err == -3)
		return ("Map is not rectangular");
	if (err == -4)
		return ("Map is missing walls");
	if (err == -5)
		return ("Map is missing player start");
	if (err == -6)
		return ("Map is not solvable");
	if (err == -20)
		return ("Map is missing collectibles");
	if (err == -21)	
		return ("Map has invalid amount of exits");
	if (err == -22)
		return ("Map has invalid amount of players");
	return ("Unknown error");
}

static bool set_textures(mlx_texture_t **textures)
{
	int i;
	int j;

	i = 0;
	textures[IMG_WALL] = mlx_load_png("gfx/wall.png");
	textures[IMG_FLOOR] = mlx_load_png("gfx/floor.png");
	textures[IMG_COLLECT] = mlx_load_png("gfx/collect.png");
	textures[IMG_EXIT] = mlx_load_png("gfx/exit.png");
	textures[IMG_PLAYER] = mlx_load_png("gfx/player.png");
	textures[IMG_ERROR] = mlx_load_png("gfx/error.png");
	while (i < 6)
	{
		j = 0;
		if (textures[i] == NULL)
		{
			while (j < i)
				mlx_delete_texture(textures[j++]);
			return (false);
		}
		i++;
	}
	return (true);
}

static mlx_texture_t **gettextures(void)
{
	static mlx_texture_t **textures = NULL;
	if (!textures)
	{
		textures = malloc(sizeof(mlx_texture_t *) * 6);
		if (!textures)
			return (NULL);
		if (!set_textures(textures))
			return (free(textures), NULL);
	}
	return (textures);
}

static void deletetextures(void)
{
	mlx_texture_t **textures;
	int i;

	textures = gettextures();
	i = 0;
	if (!textures)
		return;
	while (i < 6)
	{
		if (textures[i] != NULL)
			mlx_delete_texture(textures[i++]);
	}
	free(textures);
}

static mlx_image_t **getmapimgs(char **map, mlx_t *mlx)
{
	// create image for each tile in map
	// set image to correct texture
	// return array of images
	// we make static and return so we can call it again later and free them
	// will also be used by a separate draw map function that we only need to use once

	// next step is a draw_objects function that creates 1 image for each object and the player
	// and then if player moves, change the x/y of the image rather than redrawing
	// this will reveal the tile below where the player currently was so no redraw ther either? supposedly
	// if collectible is collected, set the image for it to enabled=false I guess?
}

int start_game(void)
{
	char *rawmap;

	rawmap = getsetrawmap(NULL, FALSE);
	mlx_t *mlx = mlx_init(getmapwidth(rawmap) * 32, 
		getmapheight(rawmap) * 32, "So Long", false);
	if (mlx == NULL)
		return (errormsg("Failed to initialize MLX"), -1);
	mlx_loop_hook(mlx, &handle_keypress, mlx);
	mlx_loop_hook(mlx, &update_game, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

int main(int argc, char** argv)
{
	char *rawmap;
	char **map;
	int mapreturn;

	if (argc != 2)
		return(errormsg("Invalid number of arguments"), -1);
	rawmap = getrawmap(argv[1]);
	if (rawmap == NULL)
		return(errormsg("Invalid map file"), -1);
	mapreturn = verifymap(rawmap);
	if (verifymap(rawmap) != 1)
		return (errormsg(get_map_err(mapreturn)), -1);
	map = getsplitmap(rawmap);
	if (map == NULL)
		return (errormsg("Failed to split map"), -1);
	getsetrawmap(rawmap, FALSE);
	getsetmap(map, FALSE);
	mapreturn = start_game();
	return (mapreturn);
}
