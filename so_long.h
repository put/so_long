/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:01:06 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/06 01:32:31 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h> // TODO: Verify all libs are allowed and actually used before submitting
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "bool.h"
# include "libft/libft.h"

typedef struct {
	char	*rawmap;
	char	**map;
	int		width;
	int		height;
	int		collectibles_count;
	t_bool is_valid;
} t_map;

char *read_file_to_string(const char *filename);
#endif