/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschippe <mschippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:45:17 by mschippe          #+#    #+#             */
/*   Updated: 2025/01/16 16:04:07 by mschippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool coordcompare(t_tile coord1, t_tile coord2)
{
	return (coord1.x == coord2.x && coord1.y == coord2.y);
}