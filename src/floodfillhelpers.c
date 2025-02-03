/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfillhelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:45:17 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 23:13:21 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

bool	should_skip(char **map, t_tile p, int width, int height)
{
	return (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height
		|| map[p.y][p.x] == '1' || map[p.y][p.x] == '2');
}

t_tile	*maketile(int x, int y)
{
	t_tile	*tile;

	tile = malloc(sizeof(t_tile));
	if (!tile)
		return (NULL);
	*tile = (t_tile){x, y};
	return (tile);
}

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
