/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:50:16 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 16:54:02 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Prints an error message to the console in the format that
 * so_long subject expects
 * @param msg - The message to print
 */
void	errormsg(char *msg)
{
	ft_printf("Error\n%s\n", msg);
}

/**
 * Returns the error message for the given error code
 * @param err - The error code to get the message for
 * @return the error message for the given error code
 */
char	*get_map_err(int err)
{
	if (err == -1)
		return ("Failed to split map");
	if (err == -3)
		return ("Map is not rectangular");
	if (err == -4)
		return ("Map is missing walls");
	if (err == -5)
		return ("Map is missing player start");
	if (err == -6)
		return ("Map is not solvable");
	if (err == -20)
		return ("Map is missing collectibles");
	if (err == -21)
		return ("Map has invalid amount of exits");
	if (err == -22)
		return ("Map has invalid amount of players");
	return ("Unknown error");
}
