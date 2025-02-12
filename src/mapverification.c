/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapverification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:39:00 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 19:01:38 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Floodfill algorithm that fills any reachable non-wall tile with '2'
 * @param map - The map to fill
 * @param start - The starting tile for the floodfill
 * @param width - The width of the map
 * @param height - The height of the map
 * @return the filled map
 */
char	**floodfill(char **map, t_tile *start, int width, int height)
{
	t_list	*queue;
	t_tile	*c;
	t_list	*curr;

	queue = NULL;
	ft_lstadd_back(&queue, ft_lstnew(start));
	while (queue)
	{
		curr = ft_lstpop(&queue);
		if (!curr)
			return (errormsg("failed to pop from queue"), NULL);
		c = curr->content;
		free(curr);
		if (!should_skip(map, *c, width, height))
		{
			map[c->y][c->x] = '2';
			if (!add_all_to_queue(&queue, c))
				return (errormsg("failed to add to queue"), NULL);
		}
		free(c);
	}
	return (map);
}

/**
 * Verifies that the map is solvable based on given flooded map
 * @param map - The map to verify
 * @return true if the map is solvable, false otherwise
 */
bool	floodsuccess(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

/**
 * Verifies that the map is surrounded by walls
 * @param map - The map to verify
 * @param width - The width of the map
 * @return true if the map is surrounded by walls, false otherwise
 */
bool	verifywalls(char **map, int width)
{
	int	row;
	int	charindex;

	if (!map)
		return (false);
	row = 0;
	charindex = 0;
	while (map[row])
	{
		if (row == 0 || !map[row + 1])
		{
			while (map[row][charindex])
			{
				if (map[row][charindex++] != MAP_WALL)
					return (false);
			}
			charindex = 0;
		}
		else if (map[row][0] != MAP_WALL || map[row][width - 1] != MAP_WALL)
			return (false);
		row++;
	}
	return (true);
}

/**
 * Verifies that the map has the correct amount of objects
 * @param rawmap - The raw map string to verify
 * @return 1 if the map is valid, otherwise an error code
 */
int	verifyobjects(char *rawmap)
{
	int	collectibles;
	int	exits;
	int	players;
	int	other;
	int	x;

	collectibles = 0;
	exits = 0;
	players = 0;
	other = 0;
	x = 0;
	while (rawmap[x++])
	{
		if (rawmap[x - 1] == MAP_COLLECT)
			collectibles++;
		else if (rawmap[x - 1] == MAP_EXIT)
			exits++;
		else if (rawmap[x - 1] == MAP_START)
			players++;
		else if (rawmap[x - 1] != MAP_EMPTY && rawmap[x - 1] != '\n'
			&& rawmap[x - 1] != MAP_WALL)
			other++;
	}
	return (getverificationreturnvalue(players, collectibles, exits, other));
}

/**
 * Verifies that the map is rectangular
 * @param rawmap - The raw map string to verify
 * @param width - The width of the map
 * @return true if the map is rectangular, false otherwise
 */
bool	verifyrect(char *rawmap, int width)
{
	int	len;

	len = 0;
	while (*rawmap)
	{
		if (*rawmap == '\n' && len != width)
			return (false);
		else if (*rawmap == '\n')
			len = 0;
		else
			len++;
		rawmap++;
	}
	return (len == width);
}
