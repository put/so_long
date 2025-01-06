/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:51:13 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/06 03:00:10 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H
# define MAP_EMPTY '0'
# define MAP_COLLIDE '1'
# define MAP_COLLECT 'C'
# define MAP_EXIT 'E'
# define MAP_START 'P'

# include "so_long.h"

int		getmapwidth(char *rawmap);
int		getmapheight(char *rawmap);
char	**getsplitmap(char *rawmap);
t_bool	verifyrect(char *rawmap, int width);
t_bool	verifywalls(char **map, int width);
t_bool	verifyobjects(char *rawmap);
#endif