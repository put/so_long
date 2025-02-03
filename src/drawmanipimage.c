/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmanipimage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:28:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 23:02:21 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	update_playerimg(t_tile newloc)
{
	mlx_image_t	*playerimg;

	playerimg = *getplayerimg(getsetrawmap(NULL, false),
			*getsetmap(NULL, false), NULL);
	playerimg->instances[0].x = newloc.x * 32;
	playerimg->instances[0].y = newloc.y * 32;
}

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

