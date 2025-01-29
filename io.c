/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:18:53 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/29 18:15:08 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *readmapfile(const char *filename)
{
	int fd;
	char *res;
	char *temp;
	char *temp2;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	temp = get_next_line(fd);
	while (temp)
	{
		temp2 = ft_strjoin(res, temp);
		if (!temp2)
			return (free(temp), free(res), NULL);
		free(res);
		res = temp2;
		free(temp);
		temp = get_next_line(fd);
	}
	return (res);
}
