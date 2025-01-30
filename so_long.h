/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:01:06 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/30 20:18:03 by mschippe         ###   ########.fr       */
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

typedef enum t_imgtype
{
	IMG_WALL,
	IMG_FLOOR,
	IMG_COLLECT,
	IMG_EXIT,
	IMG_PLAYER,
	IMG_ERROR
} t_imgtype;

// Holds the data for a single tile on the map
typedef struct t_tile
{
				// X coordinate of the tile
	int			x;
				// Y coordinate of the tile
	int			y;
				// The type of tile this is
}	t_tile;

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
int		verifyobjects(char *rawmap);
void	print_map(char **map, int height, int width);
char	**floodfill(char **map, t_tile *start, int width, int height);
char	*readmapfile(const char *filename);
int		getcollcount(char **map);
t_tile	getcollatindex(char **map, int index);
t_tile	simpleplayerloc(char **map);
#endif