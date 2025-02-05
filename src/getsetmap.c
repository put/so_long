/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsetmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:33:09 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 16:43:50 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Checks if the given file is a valid .ber file and reads it into a string
 * @param filename - The name of the file to read
 * @return the contents of the file as a string
 */
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

/**
 * Returns the raw map string for the game
 * @param newmap - The new map to set
 * @param clear - Whether to clear the map
 * @return the raw map string for the game
 */
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

/**
 * Returns the map array for the game
 * @param newmap - The new map to set
 * @param clear - Whether to clear the map
 * @return the map array for the game
 */
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

/**
 * Splits the raw map string into a 2D array
 * @param rawmap - The raw map string to split
 * @return the 2D array of the map
 */
char	**getsplitmap(char *rawmap)
{
	return (ft_split(rawmap, '\n'));
}
