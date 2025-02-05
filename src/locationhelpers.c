/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locationhelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:35:31 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 16:47:05 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Returns the location of the player on the map
 * @param map - The map to search
 * @return the location of the player on the map
 */
t_tile	*getplayerloc(char **map)
{
	int		x;
	int		y;
	t_tile	*loc;

	y = 0;
	loc = malloc(sizeof(t_tile));
	if (loc == NULL)
		return (NULL);
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'P')
			{
				*loc = (t_tile){x, y};
				return (loc);
			}
			x++;
		}
		y++;
	}
	return (loc);
}

/**
 * Updates a tile to move in one direction from a previous location
 * @param loc - The previous location
 * @param dir - The direction to move
 * @return the new location
 */
t_tile	getnewloc(t_tile loc, t_direction dir)
{
	t_tile	newloc;

	newloc = (t_tile){loc.x, loc.y};
	if (dir == UP)
		newloc.y--;
	if (dir == DOWN)
		newloc.y++;
	if (dir == LEFT)
		newloc.x--;
	if (dir == RIGHT)
		newloc.x++;
	return (newloc);
}

/**
 * Gets and sets the exit location on the map
 * @param tile - The tile to set as the exit
 * @param update - Whether to update the exit location
 * @return the exit location
 */
t_tile	getsetexit(t_tile tile, bool update)
{
	static t_tile	exit = (t_tile){-1, -1};

	if (update)
	{
		exit.x = tile.x;
		exit.y = tile.y;
	}
	return (exit);
}

/**
 * Returns the exit location on the map
 * @return the exit location
 */
t_tile	getexit(void)
{
	return (getsetexit((t_tile){0, 0}, false));
}

/**
 * Compares two tiles to see if they are the same
 * @param coord1 - The first tile to compare
 * @param coord2 - The second tile to compare
 * @return true if the tiles are the same, false otherwise
 */
bool	comp_coords(t_tile coord1, t_tile coord2)
{
	return (coord1.x == coord2.x && coord1.y == coord2.y);
}
