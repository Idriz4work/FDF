/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_connecter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:40 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 22:26:18 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Function to put a pixel in an image
void	put_pixel_to_image(t_map *map, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}
