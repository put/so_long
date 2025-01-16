/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:32:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/16 19:43:23 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Takes a raw map (no processing) and counts
// how many characters are in the first line
int	getmapwidth(char *rawmap)
{
	int	x;

	x = 0;
	if (!rawmap)
		return (x);
	while (rawmap[x] != '\n' && rawmap[x])
		x++;
	return (x);
}

// Takes a raw map (no processing) and counts
// how many newlines are in the string
int	getmapheight(char *rawmap)
{
	int	y;

	y = 0;
	if (!rawmap)
		return (y);
	while (*rawmap)
	{
		if (*rawmap == '\n')
			y++;
		rawmap++;
	}
	return (y + 1);
}

// Verifies that the map is rectangular
t_bool	verifyrect(char *rawmap, int width)
{
	int	len;

	len = 0;
	while (*rawmap)
	{
		if (*rawmap == '\n' && len != width)
			return (FALSE);
		else if (*rawmap == '\n')
			len = 0;
		else
			len++;
		rawmap++;
	}
	return (len == width);
}

// Splits the raw map into an array of strings
char	**getsplitmap(char *rawmap)
{
	return (ft_split(rawmap, '\n'));
}

// Verifies that the map is surrounded by walls
t_bool	verifywalls(char **map, int width)
{
	int	row;
	int	charindex;

	if (!map)
		return (FALSE);
	row = 0;
	charindex = 0;
	while (map[row])
	{
		if (row == 0 || !*(map + 1))
		{
			while (map[row][charindex])
			{
				if (map[row][charindex++] != MAP_WALL)
					return (FALSE);
			}
			charindex = 0;
		}
		else if (map[row][0] != MAP_WALL || map[row][width - 1] != MAP_WALL)
			return (FALSE);
		row++;
	}
	return (TRUE);
}

// Verifies that the map has at least one collectible, one exit, and one player
t_bool	verifyobjects(char *rawmap)
{
	int	collectibles;
	int	exits;
	int	player;
	int	x;

	collectibles = 0;
	exits = 0;
	player = 0;
	x = 0;
	while (rawmap[x])
	{
		if (rawmap[x] == MAP_COLLECT)
			collectibles++;
		else if (rawmap[x] == MAP_EXIT)
			exits++;
		else if (rawmap[x] == MAP_START)
			player++;
		x++;
	}
	return (collectibles > 0 && exits == 1 && player == 1);
}

// Verifies that a given coordinate is within the bounds of the map
t_bool	in_bounds(t_map map, t_tile coord)
{
	return (coord.x >= 0 && coord.x < map.width
		&& coord.y >= 0 && coord.y < map.height);
}

// Initializes the map tiles within the given map
int	init_map_tiles(t_map **map, char **smap, int width, int height)
{
	int	i;
	int	j;
	int	allocs;

	i = 0;
	j = 0;
	allocs = 0;
	while (allocs < (*map)->height)
	{
		(*map)->map[allocs] = (t_tile *)malloc(sizeof(t_tile) * (*map)->width);
		if (!(*map)->map[allocs])
			return (allocs);
		allocs++;
	}
	while (j < (*map)->height)
	{
		i = 0;
		while (i < (*map)->width)
		{
			(*map)->map[j][i] = (t_tile){i, j, (t_tiletype)smap[j][i], 0};
			i++;
		}
		j++;
	}
	return (allocs);
}

// Creates a complete map struct from a split map
// Still needs a free_map function to free the map
t_map	*create_map(char **splitmap, int width, int height)
{
	t_map	*map;
	int		goodmallocs;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	goodmallocs = 0;
	map->width = width;
	map->height = height;
	map->map = (t_tile **)malloc(sizeof(t_tile *) * map->height);
	if (!map->map)
		return (free(map), NULL);
	goodmallocs = init_map_tiles(&map, splitmap, width, height);
	if (goodmallocs < map->height)
	{
		while (goodmallocs >= 0)
			free(map->map[goodmallocs--]);
		free(map->map);
		free(map);
		return (NULL);
	}
	return (map);
}

void	print_map(t_map *map) // TODO: Delete before handing in, debug only
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			printf("%c", map->map[i][j++].tile);
		printf("\n");
		i++;
	}
}
