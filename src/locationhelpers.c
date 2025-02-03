/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locationhelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:35:31 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 23:03:20 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

t_tile	getexit(void)
{
	return (getsetexit((t_tile){0, 0}, false));
}

bool	comp_coords(t_tile coord1, t_tile coord2)
{
	return (coord1.x == coord2.x && coord1.y == coord2.y);
}
