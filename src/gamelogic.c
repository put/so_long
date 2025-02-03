/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamelogic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:51:11 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 22:53:30 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.action != MLX_PRESS)
		return ;
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

static int	verifymap(char *rawmap)
{
	int		width;
	int		height;
	char	**map;
	t_tile	*playerloc;
	int		objectreturn;

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

static void	checkforwin(char **map, t_tile newloc, mlx_t *mlx)
{
	if (getexit().x == newloc.x && getexit().y == newloc.y
		&& getcollcount(map) == 0)
	{
		mlx_close_window(mlx);
		ft_printf("You win!\n");
	}
}

static void	do_movement(t_direction dir, mlx_t *mlx)
{
	char		**map;
	static int	move_count = 0;
	t_tile		oldloc;
	t_tile		newloc;

	map = *getsetmap(NULL, false);
	oldloc = simpleplayerloc(map);
	newloc = getnewloc(oldloc, dir);
	if (map[newloc.y][newloc.x] == '1')
		return ;
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

int	start_game(void)
{
	char		*rawmap;
	mlx_t		*mlx;
	mlx_image_t	***mapimgs;
	mlx_image_t	***objimgs;

	rawmap = getsetrawmap(NULL, false);
	mlx = mlx_init(getmapwidth(rawmap) * 32,
			getmapheight(rawmap) * 32, "So Long", false);
	if (mlx == NULL)
		return (errormsg("Failed to initialize MLX"), -1);
	mlx_key_hook(mlx, &handle_keypress, mlx);
	draw_map(mlx);
	draw_objs(mlx);
	mlx_loop(mlx);
	deletetextures();
	mapimgs = getmapimgs(getsetrawmap(NULL, false),
			*getsetmap(NULL, false), mlx);
	objimgs = getobjimgs(*getsetmap(NULL, false), mlx);
	free(*mapimgs);
	free(*objimgs);
	mlx_terminate(mlx);
	return (0);
}
