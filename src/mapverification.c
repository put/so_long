/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapverification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:39:00 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 15:29:17 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

// Verifies that the map is surrounded by walls
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

// Verifies that the map has at least one collectible, one exit, and one player
int	verifyobjects(char *rawmap)
{
	int	collectibles;
	int	exits;
	int	player;
	int	x;

	collectibles = 0;
	exits = 0;
	player = 0;
	x = 0;
	while (rawmap[x++])
	{
		if (rawmap[x - 1] == MAP_COLLECT)
			collectibles++;
		else if (rawmap[x - 1] == MAP_EXIT)
			exits++;
		else if (rawmap[x - 1] == MAP_START)
			player++;
	}
	if (collectibles <= 0)
		return (-20);
	if (exits != 1)
		return (-21);
	if (player != 1)
		return (-22);
	return (1);
}

// Verifies that the map is rectangular
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
