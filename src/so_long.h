/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:01:06 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/03 23:14:58 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h> // TODO: Verify all libs are allowed & used
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

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
}	t_imgtype;

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

// getsetimage.c
bool				set_textures(mlx_texture_t **textures);
mlx_texture_t		**gettextures(void);
mlx_image_t			***getmapimgs(char *rawmap, char **map, mlx_t *mlx);
mlx_image_t			***getobjimgs(char **map, mlx_t *mlx);
mlx_image_t			**getplayerimg(char *rawmap, char **map, mlx_t *mlx);

// drawmanipimage.c
void				draw_objs(mlx_t *mlx);
void				draw_map(mlx_t *mlx);
void				hide_collectible(int x, int y);
void				update_playerimg(t_tile newloc);
t_imgtype			get_tiletype(char c);

// getsetmap.c
char				*getrawmap(char *filename);
char				*getsetrawmap(char *newmap, bool clear);
char				***getsetmap(char **newmap, bool clear);
char				**getsplitmap(char *rawmap);

// locationhelpers.c
t_tile				*getplayerloc(char **map);
t_tile				getnewloc(t_tile loc, t_direction dir);
t_tile				getsetexit(t_tile tile, bool update);
t_tile				getexit(void);
bool				comp_coords(t_tile coord1, t_tile coord2);

// floodfillhelpers.c
t_list				*ft_lstpop(t_list **queue);
int					sideval(int index, bool is_dx);
bool				should_skip(char **map, t_tile p, int width, int height);
t_tile				*maketile(int x, int y);
int					add_all_to_queue(t_list **queue, t_tile *c);

// floodfill.c
char				**floodfill(char **map, t_tile *start,
						int width, int height);
bool				floodsuccess(char **map);
bool				verifywalls(char **map, int width);
bool				verifyrect(char *rawmap, int width);
int					verifyobjects(char *rawmap);

// maphelpers.c
int					getcollcount(char **map);
t_tile				getcollatindex(char **map, int index);
int					getmapwidth(char *rawmap);
int					getmapheight(char *rawmap);
t_tile				simpleplayerloc(char **map);

/// cleanup.c
void				freestrarr(char **arr);
void				deletetextures(void);

// errors.c
void				errormsg(char *msg);
char				*get_map_err(int err);

// gamelogic.c
int					start_game(void);
void				do_movement(t_direction dir, mlx_t *mlx);
void				checkforwin(char **map, t_tile newloc, mlx_t *mlx);
void				handle_keypress(mlx_key_data_t keydata, void *param);
int					verifymap(char *rawmap);

// io.c
char				*readmapfile(const char *filename);

// main.c
int					main(int argc, char **argv);
#endif
