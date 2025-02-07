/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmanipimage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:28:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 16:34:38 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Draws collectibles and the player to the MLX window
 * @param mlx - An already initialized MLX instance
 */
void	draw_objs(mlx_t *mlx)
{
	mlx_image_t	**imgs;
	mlx_image_t	*player;
	int			index;
	int			count;
	t_tile		p;

	index = 0;
	count = getcollcount(*getsetmap(NULL, false));
	imgs = *getobjimgs(*getsetmap(NULL, false), mlx);
	while (index < count)
	{
		p = getcollatindex(*getsetmap(NULL, false), index);
		if (p.x != -1)
			mlx_image_to_window(mlx, imgs[index], p.x * 32, p.y * 32);
		index++;
	}
	player = *getplayerimg(getsetrawmap(NULL, false),
			*getsetmap(NULL, false), mlx);
	p = simpleplayerloc(*getsetmap(NULL, false));
	mlx_image_to_window(mlx, player, p.x * 32, p.y * 32);
}

/**
 * Draws the base map to the MLX window
 * @param mlx - An already initialized MLX instance
 */
void	draw_map(mlx_t *mlx)
{
	mlx_image_t	**imgs;
	int			x;
	int			y;
	int			total;

	imgs = *getmapimgs(getsetrawmap(NULL, false),
			*getsetmap(NULL, false), mlx);
	x = 0;
	total = 0;
	while (x < getmapwidth(getsetrawmap(NULL, false)))
	{
		y = 0;
		while (y < getmapheight(getsetrawmap(NULL, false)))
		{
			mlx_image_to_window(mlx, imgs[total], x * 32, y * 32);
			total++;
			y++;
		}
		x++;
	}
}

/**
 * Loops through all object images and disables the one at the given location
 * @param x - The x coordinate of the object to hide
 * @param y - The y coordinate of the object to hide
 */
void	hide_collectible(int x, int y)
{
	mlx_image_t	**imgs;
	int			count;

	imgs = *getobjimgs(*getsetmap(NULL, false), NULL);
	count = 0;
	while (imgs[count])
	{
		if (imgs[count]->instances[0].x == x * 32
			&& imgs[count]->instances[0].y == y * 32)
		{
			imgs[count]->instances[0].enabled = false;
			break ;
		}
		count++;
	}
}

/**
 * Updates the player image to the new location
 * @param newloc - The new location of the player
 */
void	update_playerimg(t_tile newloc)
{
	mlx_image_t	*playerimg;

	playerimg = *getplayerimg(getsetrawmap(NULL, false),
			*getsetmap(NULL, false), NULL);
	playerimg->instances[0].x = newloc.x * 32;
	playerimg->instances[0].y = newloc.y * 32;
}

/**
 * Returns the image index of the given tile type
 * @param c - The tile character to check (1, 0, C, E, P)
 * @return the image index of the given tile type (enumerated)
 */
t_imgtype	get_tiletype(char c)
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
