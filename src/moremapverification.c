/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moremapverification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:54:24 by mschippe          #+#    #+#             */
/*   Updated: 2025/02/05 19:02:09 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Gets the correct error code based on what the verification
 * function found in the map
 * @param players - The amount of players in the map
 * @param collectibles - The amount of collectibles in the map
 * @param exits - The amount of exits in the map
 * @param other - The amount of other objects in the map
 */
int	getverificationreturnvalue(int players, int collectibles,
	int exits, int other)
{
	if (collectibles <= 0)
		return (-20);
	if (exits != 1)
		return (-21);
	if (players != 1)
		return (-22);
	if (other != 0)
		return (-23);
	return (1);
}
