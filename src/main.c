/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:54:47 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/04 15:40:37 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	*rawmap;
	char	**map;
	int		mapreturn;

	if (argc != 2)
		return (errormsg("Invalid number of arguments"), -1);
	rawmap = getrawmap(argv[1]);
	if (rawmap == NULL)
		return (errormsg("Invalid map file"), -1);
	mapreturn = verifymap(rawmap);
	if (mapreturn != 1)
		return (errormsg(get_map_err(mapreturn)), free(rawmap), -1);
	map = getsplitmap(rawmap);
	if (map == NULL)
		return (errormsg("Failed to split map"), freestrarr(map),
			free(rawmap), -1);
	getsetrawmap(rawmap, false);
	getsetmap(map, false);
	mapreturn = start_game();
	freestrarr(map);
	free(rawmap);
	return (mapreturn);
}
