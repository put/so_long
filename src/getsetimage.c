/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsetimage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:23:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 23:16:14 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	set_textures(mlx_texture_t **textures)
{
	int	i;
	int	j;

	i = 0;
	textures[IMG_WALL] = mlx_load_png("textures/wall.png");
	textures[IMG_FLOOR] = mlx_load_png("textures/floor.png");
	textures[IMG_COLLECT] = mlx_load_png("textures/collectible.png");
	textures[IMG_EXIT] = mlx_load_png("textures/exit.png");
	textures[IMG_PLAYER] = mlx_load_png("textures/player.png");
	textures[IMG_ERROR] = mlx_load_png("textures/error.png");
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

mlx_texture_t	**gettextures(void)
{
	static mlx_texture_t	**textures = NULL;

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

mlx_image_t	***getmapimgs(char *rawmap, char **map, mlx_t *mlx)
{
	static mlx_image_t	**imgs = NULL;
	t_tile				p;
	static int			total = 0;

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
	return (&imgs);
}

mlx_image_t	***getobjimgs(char **map, mlx_t *mlx)
{
	static mlx_image_t	**imgs = NULL;
	int					count;
	int					i;

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
				return (NULL);
		}
		imgs[i] = NULL;
	}
	return (&imgs);
}

mlx_image_t	**getplayerimg(char *rawmap, char **map, mlx_t *mlx)
{
	static mlx_image_t	*player = NULL;
	int					x;
	int					y;

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
