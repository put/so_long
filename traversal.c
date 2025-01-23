/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:45:17 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/22 20:15:11 by mschippe         ###   ########.fr       */
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

char *floodfill(char *raw, char **map, int start_x, int start_y)
{
    int width;
    int height;
	t_list *queue;
	t_tile *start;
	t_tile *c;
	int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
	height = getmapheight(raw);
	width = getmapwidth(raw);
	queue = NULL;
	start = malloc(sizeof(t_tile));
    start->x = start_x;
    start->y = start_y;
    ft_lstadd_back(&queue, ft_lstnew(start));
    while (queue)
    {
        t_tile *c = queue->content;
        queue = queue->next;
        if (c->x < 0 || c->x >= width || c->y < 0 || c->y >= height ||
            map[c->y][c->x] == '1' || map[c->y][c->x] == '2')
            continue;
        map[c->y][c->x] = '2';
        for (int i = 0; i < 4; i++)
        {
            t_tile *next = malloc(sizeof(t_tile));
            next->x = c->x + dx[i];
            next->y = c->y + dy[i];
            ft_lstadd_back(&queue, ft_lstnew(next));
        }
        free(c);
    }
}
