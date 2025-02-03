/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maphelpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:32:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 22:46:07 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Takes a raw map (no processing) and counts
// how many characters are in the first line
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

// Takes a raw map (no processing) and counts
// how many newlines are in the string
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
