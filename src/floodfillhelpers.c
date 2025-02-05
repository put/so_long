/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfillhelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:45:17 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 16:54:36 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Pops the first element from the queue (extension for libft linkedlists)
 * @param queue - The queue to pop from
 * @return the first element of the queue
 */
t_list	*ft_lstpop(t_list **queue)
{
	t_list	*tmp;

	if (!queue || !*queue)
		return (NULL);
	tmp = *queue;
	*queue = (*queue)->next;
	tmp->next = NULL;
	return (tmp);
}

/**
 * Returns the correct value for the given index and direction
 * (left/right or up/down)
 * @param index - The index to check (0, 1, 2, 3)
 * @param is_dx - Whether to check the x direction or y direction
 * @return a value of 1 or -1 depending on the index and direction
 */
int	sideval(int index, bool is_dx)
{
	if (is_dx)
	{
		if (index == 0)
			return (1);
		if (index == 1)
			return (-1);
	}
	else
	{
		if (index == 2)
			return (1);
		if (index == 3)
			return (-1);
	}
	return (0);
}

/**
 * Returns whether the given tile should be skipped in the floodfill algorithm
 * @param map - The map to check against
 * @param p - The tile to check
 * @param width - The width of the map
 * @param height - The height of the map
 * @return true if the tile should be skipped, false otherwise
 */
bool	should_skip(char **map, t_tile p, int width, int height)
{
	return (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height
		|| map[p.y][p.x] == '1' || map[p.y][p.x] == '2');
}

/**
 * Creates a new (malloc'ed) tile struct with the given x and y values
 * @param x - The x value of the tile
 * @param y - The y value of the tile
 * @return the new tile struct
 */
t_tile	*maketile(int x, int y)
{
	t_tile	*tile;

	tile = malloc(sizeof(t_tile));
	if (!tile)
		return (NULL);
	*tile = (t_tile){x, y};
	return (tile);
}

/**
 * Adds all adjacent tiles to the queue
 * @param queue - The queue to add to
 * @param c - The current tile to add from
 * @return 1 if successful, 0 if malloc fails
 */
int	add_all_to_queue(t_list **queue, t_tile *c)
{
	t_tile	*next;
	int		i;

	i = 0;
	while (i < 4)
	{
		next = maketile(c->x + sideval(i, 1), c->y + sideval(i, 0));
		if (!next)
			return (0);
		ft_lstadd_back(queue, ft_lstnew(next));
		i++;
	}
	return (1);
}
