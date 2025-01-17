/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:01:06 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/17 20:11:07 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h> // TODO: Verify all libs are allowed & used
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "bool.h"
# include "libft/libft.h"

// Holds the characters that represent the map
typedef enum t_tiletype
{
	// Out of bounds
	OOB = 0,
	// Empty, walkable tile
	MAP_EMPTY = '0',
	// Collision tile, not walkable
	MAP_WALL = '1',
	// Collectible item, is walkable
	MAP_COLLECT = 'C',
	// Exit tile, is walkable
	// Only ends game once all collectibles are collected
	MAP_EXIT = 'E',
	// Player start tile, is walkable
	MAP_START = 'P'
}	t_tiletype;

// Holds the data for a single tile on the map
typedef struct t_tile
{
				// X coordinate of the tile
	int			x;
				// Y coordinate of the tile
	int			y;
				// The type of tile this is
	t_tiletype	tile;
				// Whether this tile has been visited (map validation)
	t_bool		visited;
}	t_tile;

// Holds the map data
typedef struct t_map
{
			// 2D array of map tiles
	t_tile	**map;
			// Width of the map
	int		width;
			// Height of the map
	int		height;
			// The amount of collectibles that are inside the map
	int		collectibles_count;
}	t_map;

// Holds the direction the player is moving
typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_direction;

int		getmapwidth(char *rawmap);
int		getmapheight(char *rawmap);
char	**getsplitmap(char *rawmap);
t_bool	verifyrect(char *rawmap, int width);
t_bool	verifywalls(char **map, int width);
t_bool	verifyobjects(char *rawmap);
t_bool	in_bounds(t_map map, t_tile coord);
char	*read_file_to_string(const char *filename);
t_map	*create_map(char **splitmap, int width, int height);
void	print_map(t_map *map);
t_list	*floodfill(t_map *map, t_tile start);
#endif