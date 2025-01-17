/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:54:47 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/17 20:20:59 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(void) // TODO: Add ft_printf to the project to replace printf
{
	char *rawmap;
	char **map;
	int width;
	int height;
	int collectibles_count;

	rawmap = "1111111111\n1000000001\n10P0000C01\n1000000001\n1000000001\n1000000001\n1000000001\n1C0000C001\n10000000E1\n1111111111";
	width = getmapwidth(rawmap);
	height = getmapheight(rawmap);
	printf("Map size is %i by %i\n", width, height);
	if(verifyrect(rawmap, width))
	{
		printf("Map is rectangular\n");
		map = getsplitmap(rawmap);
		if (verifywalls(map, width))
		{
			printf("Map is correctly surrounded by walls\n");
			if (verifyobjects(rawmap))
				printf("Map has proper objects\n");
			else
				printf("ERROR: Map does NOT have proper objects!\n");
		}
		else
			printf("ERROR: Map does NOT have proper walls!\n");
	}
	else
		printf("ERROR: Map is NOT rectangular!\n");
	t_map *goodmap = create_map(map, width, height);
	if (goodmap)
		printf("Map created successfully\n");
	else
		printf("ERROR: Map creation failed\n");
	print_map(goodmap);
	t_list *queue = floodfill(goodmap, (t_tile){1, 1, MAP_START, FALSE});

	while (queue)
	{
		t_tile *current = (t_tile *)queue->content;
		printf("Visited tile at %i, %i\n", current->x, current->y);
		queue = queue->next;
	}
}
