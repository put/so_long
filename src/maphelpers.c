/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maphelpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:32:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 16:49:42 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Returns the width of the map
 * @param rawmap - The raw map string to get the width of
 * @return the width of the map
 */
int	getmapwidth(char *rawmap)
{
	int	x;

	x = 0;
	if (!rawmap)
		return (x);
	while (rawmap[x] != '\n' && rawmap[x])
		x++;
	return (x);
}

/**
 * Returns the height of the map
 * @param rawmap - The raw map string to get the height of
 * @return the height of the map
 */
int	getmapheight(char *rawmap)
{
	int	y;

	y = 0;
	if (!rawmap)
		return (y);
	while (*rawmap)
	{
		if (*rawmap == '\n')
			y++;
		rawmap++;
	}
	return (y + 1);
}

/**
 * Finds the amount of collectibles in the map
 * @param map - The map to search
 * @return the amount of collectibles in the map
 */
int	getcollcount(char **map)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == MAP_COLLECT)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/**
 * Returns the location of the collectible at the given index
 * @param map - The map to search
 * @param index - The index of the collectible to find
 * @return the location of the collectible at the given index
 */
t_tile	getcollatindex(char **map, int index)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == MAP_COLLECT)
			{
				if (count == index)
					return ((t_tile){x, y});
				count++;
			}
			x++;
		}
		y++;
	}
	return ((t_tile){-1, -1});
}

/**
 * Returns the location of the player on the map (non-malloc'ed tile)
 * @param map - The map to search
 * @return the location of the player on the map
 */
t_tile	simpleplayerloc(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == MAP_START)
				return ((t_tile){x, y});
			x++;
		}
		y++;
	}
	return ((t_tile){-1, -1});
}
