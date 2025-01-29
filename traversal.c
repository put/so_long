/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:45:17 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/29 17:53:13 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool comp_coords(t_tile coord1, t_tile coord2)
{
	return (coord1.x == coord2.x && coord1.y == coord2.y);
}

t_list *ft_lstpop(t_list **queue)
{
	t_list	*tmp;

	if (!queue || !*queue)
		return (NULL);
	tmp = *queue;
	*queue = (*queue)->next;
	tmp->next = NULL;
	return (tmp);
}

int sideval(int index, t_bool is_dx)
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

t_bool should_skip(char **map, int x, int y, int width, int height)
{
	return (x < 0 || x >= width || y < 0 || y >= height ||
			map[y][x] == '1' || map[y][x] == '2');
}

t_tile *maketile(int x, int y)
{
	t_tile *tile;

	tile = malloc(sizeof(t_tile));
	if (!tile)
		return (NULL);
	*tile = (t_tile){x, y};
	return (tile);
}

int add_all_to_queue(t_list **queue, t_tile *c)
{
	t_tile *next;
	int i;

	i = 0;
	while (i < 4)
	{
		next = maketile(c->x + sideval(i, 1), c->y + sideval(i, 0));
		if (!next)
			return 0;
		ft_lstadd_back(queue, ft_lstnew(next));
		i++;
	}
	return 1;
}

char **floodfill(char **map, t_tile *start, int width, int height)
{
	t_list *queue;
	t_tile *c;
	t_list *curr;
	queue = NULL;
    ft_lstadd_back(&queue, ft_lstnew(start));
    while (queue)
    {
        curr = ft_lstpop(&queue);
        c = curr->content;
		free(curr);
		if (!should_skip(map, c->x, c->y, width, height))
        {
			map[c->y][c->x] = '2';
			if (!add_all_to_queue(&queue, c))
				return (NULL);
		}
        free(c);
    }
	return (map);
}
