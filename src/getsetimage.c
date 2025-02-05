/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsetimage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:23:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 16:42:05 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Loads textures from PNGs into the given array
 * @param textures - The array to load the textures into
 * @return true if all textures were loaded successfully, otherwise false
 */
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

/**
 * Returns the array of textures for the game
 * @return the array of textures for the game
 */
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

/**
 * Returns the array of map images for the game
 * @param rawmap - The raw map string to get the images for
 * @param map - The map to get the images for
 * @param mlx - The MLX instance to create the images with
 * @return the array of map images for the game
 */
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

/**
 * Returns the array of object images for the game
 * @param map - The map to get the images for
 * @param mlx - The MLX instance to create the images with
 * @return the array of object images for the game
 */
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

/**
 * Returns the image of the player
 * @param rawmap - The raw map string to get the player image from
 * @param map - The map to get the player image from
 * @param mlx - The MLX instance to create the image with
 * @return the image of the player
 */
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
