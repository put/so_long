/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsetmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:33:09 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 22:49:36 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*getrawmap(char *filename)
{
	char	*lastdot;

	lastdot = ft_strrchr(filename, '.');
	if (lastdot == NULL)
		return (NULL);
	if (ft_strncmp(lastdot, ".ber", 4) != 0)
		return (NULL);
	return (readmapfile(filename));
}

char	*getsetrawmap(char *newmap, bool clear)
{
	static char	*rawmap = NULL;

	if (newmap != NULL)
	{
		free(rawmap);
		rawmap = newmap;
	}
	if (clear)
		free(rawmap);
	return (rawmap);
}

char	***getsetmap(char **newmap, bool clear)
{
	static char	**map = NULL;

	if (newmap != NULL)
	{
		freestrarr(map);
		map = newmap;
	}
	if (clear)
		freestrarr(map);
	return (&map);
}

// Splits the raw map into an array of strings
char	**getsplitmap(char *rawmap)
{
	return (ft_split(rawmap, '\n'));
}
