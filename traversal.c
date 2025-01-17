/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:45:17 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/17 20:40:44 by mschippe         ###   ########.fr       */
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

t_bool *floodfill(t_map *map, t_tile *start)
{
    t_list *list = ft_lstnew(start);
	t_tile *current;

	while (list)
	{
		list = ft_lstpop(&list);
		current = (t_tile *)(list->content);
	}
}
