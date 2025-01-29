/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:54:47 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/29 22:20:27 by mschippe         ###   ########.fr       */
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

// static void set_textures(mlx_texture_t **textures)
// {
// 	textures[0] = mlx_load_png("gfx/wall.png");
// 	textures[1] = mlx_load_png("gfx/floor.png");
// 	textures[2] = mlx_load_png("gfx/collectible.png");
// 	textures[3] = mlx_load_png("gfx/exit.png");
// 	textures[4] = mlx_load_png("gfx/player.png");
// 	textures[5] = mlx_load_png("gfx/error.png");
// } // TODO: Might remove

static mlx_image_t **get_images(mlx_t *mlx)
{
    static mlx_image_t **images = NULL;
    static mlx_texture_t *textures[6] = {NULL};
    int counter;

	counter = 0;
    if (images == NULL)
    {
        images = malloc(sizeof(mlx_image_t *) * 6);
        if (images == NULL)
            return (NULL);
		textures[0] = mlx_load_png("gfx/wall.png");
		textures[1] = mlx_load_png("gfx/floor.png");
		textures[2] = mlx_load_png("gfx/collectible.png");
		textures[3] = mlx_load_png("gfx/exit.png");
		textures[4] = mlx_load_png("gfx/player.png");
		textures[5] = mlx_load_png("gfx/error.png");
        while (counter < 6)
        {
            images[counter] = mlx_texture_to_image(mlx, textures[counter]);
            if (images[counter] == NULL)
                return (free(images), NULL);
			counter++;
        }
    }
    return (images);
}

static void draw_tile(mlx_t *mlx, t_imgtype type, int x, int y)
{
    mlx_image_t **images;
    mlx_image_t *img;

    images = get_images(mlx);
    if (images == NULL)
    {
        perror("ERROR: get_images() failed\n");
        return;
    }

    img = images[type];
    mlx_image_to_window(mlx, img, x * 32, y * 32);
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
static void draw_objects(mlx_t *mlx, char **map)
{
	int x;
	int y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'C')
				draw_tile(mlx, IMG_COLLECT, x, y);
			if (map[y][x] == 'P')
				draw_tile(mlx, IMG_PLAYER, x, y);
			x++;
		}
		y++;
	}
}

static void draw_map(void *param)
{
	int x;
	int y;
	char **map;
	mlx_t *mlx;

	mlx = (mlx_t *)param;
	y = 0;
	map = *getsetmap(NULL, FALSE);
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			draw_tile(mlx, get_tiletype(map[y][x]), x, y);
			x++;
		}
		y++;
	}
	draw_objects(mlx, map);
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
