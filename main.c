/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:54:47 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 21:16:36 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/include/MLX42/MLX42.h"

static mlx_image_t **getplayerimg(char *rawmap, char **map, mlx_t *mlx);
static mlx_image_t ***getobjimgs(char **map, mlx_t *mlx);

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

t_tile getnewloc(t_tile loc, t_direction dir)
{
	t_tile newloc;

	newloc = (t_tile){loc.x, loc.y};
	if (dir == UP)
		newloc.y--;
	if (dir == DOWN)
		newloc.y++;
	if (dir == LEFT)
		newloc.x--;
	if (dir == RIGHT)
		newloc.x++;
	return (newloc);
}

static void update_playerimg(t_tile newloc)
{
	mlx_image_t *playerimg;

	playerimg = *getplayerimg(getsetrawmap(NULL, FALSE),
		*getsetmap(NULL, FALSE), NULL);

	if (playerimg == NULL)
		return; // TODO: MAYBE EXIT SHIT??
	playerimg->instances[0].x = newloc.x * 32;
	playerimg->instances[0].y = newloc.y * 32;
}

static void hide_collectible(int x, int y)
{
	mlx_image_t **imgs;
	int count;

	imgs = *getobjimgs(*getsetmap(NULL, FALSE), NULL);
	count = 0;

	while (imgs[count])
	{
		if (imgs[count]->instances[0].x == x * 32
			&& imgs[count]->instances[0].y == y * 32)
		{
			imgs[count]->instances[0].enabled = false;
			break;
		}
		count++;
	}
}

static t_tile getsetexit(t_tile tile, bool update)
{
	static t_tile exit = (t_tile){-1, -1};

	if (update)
	{
		exit.x = tile.x;
		exit.y = tile.y;
	}
	return (exit);
}

static t_tile getexit()
{
	return (getsetexit((t_tile){0, 0}, false));
}

static void checkforwin(char **map, t_tile newloc, mlx_t *mlx)
{
	if (getexit().x == newloc.x && getexit().y == newloc.y
	&& getcollcount(map) == 0)
	{
		mlx_close_window(mlx);
		ft_printf("You win!\n");
	}
}

static void do_movement(t_direction dir, mlx_t *mlx)
{
	char **map;
	static int move_count = 0;
	t_tile oldloc;
	t_tile newloc;

	map = *getsetmap(NULL, FALSE);
	oldloc = simpleplayerloc(map);
	newloc = getnewloc(oldloc, dir);
	if (map[newloc.y][newloc.x] == '1')
		return;
	if (map[newloc.y][newloc.x] == 'C')
	{
		hide_collectible(newloc.x, newloc.y);
		map[newloc.y][newloc.x] = '0';
	}
	if (map[newloc.y][newloc.x] == 'E')
		getsetexit(newloc, true);
	map[oldloc.y][oldloc.x] = '0';
	map[newloc.y][newloc.x] = 'P';
	move_count++;
	update_playerimg(newloc);
	ft_printf("Move count: %d\n", move_count);
	checkforwin(map, newloc, mlx);
}

static void handle_keypress(mlx_key_data_t keydata, void *param)
{
	mlx_t *mlx;

	mlx = (mlx_t *)param;
	if (keydata.action != MLX_PRESS)
		return;
    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(mlx);
	else if (keydata.key == MLX_KEY_W)
		do_movement(UP, mlx);
	else if (keydata.key == MLX_KEY_A)
		do_movement(LEFT, mlx);
	else if (keydata.key == MLX_KEY_S)
		do_movement(DOWN, mlx);
	else if (keydata.key == MLX_KEY_D)
		do_movement(RIGHT, mlx);
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
		return (freestrarr(map), free(playerloc), -5);
	if (!floodsuccess(floodfill(map, playerloc, width, height)))
		return (freestrarr(map), free(playerloc), -6);
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
	textures[IMG_COLLECT] = mlx_load_png("gfx/collectible.png");
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

static mlx_image_t ***getmapimgs(char *rawmap, char **map, mlx_t *mlx)
{
	static mlx_image_t **imgs = NULL;
	t_tile p;
	static int total = 0;

	p = (t_tile){0, 0};
	if (!imgs)
	{
		imgs = malloc(sizeof(mlx_image_t *) * ((getmapheight(rawmap)
			* getmapwidth(rawmap)) + 1));
		if (!imgs || !gettextures())
			return (NULL);
		while (p.x++ < getmapwidth(rawmap))
		{
			p.y = 0;
			while (p.y++ < getmapheight(rawmap))
			{
				imgs[total] = mlx_texture_to_image(mlx,
					gettextures()[get_tiletype(map[p.y - 1][p.x - 1])]);
				if (!imgs[total++])
					return (NULL);
			}
		}
		imgs[total] = NULL;
	}
	return (&imgs); // delete call here may be bad practice?! may fuck shit up
}

static mlx_image_t ***getobjimgs(char **map, mlx_t *mlx)
{
	static mlx_image_t **imgs = NULL;
	int count;
	int i;

	if (!imgs)
	{
		count = getcollcount(map);
		imgs = malloc(sizeof(mlx_image_t *) * (count + 1));
		if (!imgs || !gettextures())
			return (NULL);
		i = 0;
		while (i < count)
		{
			imgs[i] = mlx_texture_to_image(mlx, gettextures()[IMG_COLLECT]);
			if (!imgs[i++])
				return (NULL); // if this happens, should be able to call this func again and have imgs not be null and then loop through the non-null ones to destroy em and hten free pointer
		}
		imgs[i] = NULL;
	}
	return (&imgs);
}

static mlx_image_t **getplayerimg(char *rawmap, char **map, mlx_t *mlx)
{
	static mlx_image_t *player = NULL;
	int x;
	int y;

	if (!player)
	{
		x = 0;
		while (x++ < getmapwidth(rawmap))
		{
			y = 0;
			while (y++ < getmapheight(rawmap))
			{
				if (map[y - 1][x - 1] == 'P')
				{
					player = mlx_texture_to_image(mlx,
						gettextures()[IMG_PLAYER]);
					return (&player);
				}
			}
		}
	}
	return (&player);
}

static void draw_objs(mlx_t *mlx)
{
	mlx_image_t **imgs;
	mlx_image_t *player;
	int index;
	int count;
	t_tile p;

	index = 0;
	count = getcollcount(*getsetmap(NULL, FALSE));
	imgs = *getobjimgs(*getsetmap(NULL, FALSE), mlx);
	while (index < count)
	{
		p = getcollatindex(*getsetmap(NULL, FALSE), index);
		if (p.x != -1)
			mlx_image_to_window(mlx, imgs[index], p.x * 32, p.y * 32);
		index++;
	}
	player = *getplayerimg(getsetrawmap(NULL, FALSE),
		*getsetmap(NULL, FALSE), mlx);
	p = simpleplayerloc(*getsetmap(NULL, FALSE));
	mlx_image_to_window(mlx, player, p.x * 32, p.y * 32);
}

static void draw_map(mlx_t *mlx)
{
	mlx_image_t **imgs;
	int x;
	int y;
	int total;


	imgs = *getmapimgs(getsetrawmap(NULL, FALSE),
		*getsetmap(NULL, FALSE), mlx); //TODO: Prob needs error handling
	x = 0;
	total = 0;
	while (x < getmapwidth(getsetrawmap(NULL, FALSE)))
	{
		y = 0;
		while (y < getmapheight(getsetrawmap(NULL, FALSE)))
		{
			mlx_image_to_window(mlx, imgs[total], x * 32, y * 32);
			total++;
			y++;
		}
		x++;
	}
}

int start_game(void)
{
	char *rawmap;

	rawmap = getsetrawmap(NULL, FALSE);
	mlx_t *mlx = mlx_init(getmapwidth(rawmap) * 32, 
		getmapheight(rawmap) * 32, "So Long", false);
	if (mlx == NULL)
		return (errormsg("Failed to initialize MLX"), -1);
	mlx_key_hook(mlx, &handle_keypress, mlx);
	draw_map(mlx);
	draw_objs(mlx);
	mlx_loop(mlx);
	deletetextures();
	mlx_image_t ***mapimgs = getmapimgs(getsetrawmap(NULL, FALSE),
		*getsetmap(NULL, FALSE), mlx);
	mlx_image_t ***objimgs = getobjimgs(*getsetmap(NULL, FALSE), mlx);
	free(*mapimgs);
	free(*objimgs);
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
	freestrarr(map);
	free(rawmap);
	
	return (mapreturn);
}
