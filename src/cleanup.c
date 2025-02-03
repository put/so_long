/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:47:08 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 22:47:49 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	freestrarr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	deletetextures(void)
{
	mlx_texture_t	**textures;
	int				i;

	textures = gettextures();
	i = 0;
	if (!textures)
		return ;
	while (i < 6)
	{
		if (textures[i] != NULL)
			mlx_delete_texture(textures[i++]);
	}
	free(textures);
}
