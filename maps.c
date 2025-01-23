/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:32:34 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/22 20:11:30 by mschippe         ###   ########.fr       */
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

// Visualizes the map in stdout!
void	print_map(char **map, int height, int width) // TODO: Delete before handing in, debug only
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
			printf("%c", map[i][j++]);
		printf("\n");
		i++;
	}
}
