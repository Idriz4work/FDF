/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_connecter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:40 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 16:58:17 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Function to put a pixel in an image at coordinates (x,y) with specified color
// Includes boundary checking to prevent drawing outside the window
// Only draw pixels that are within the window boundaries
// Calculate the memory address for this pixel using the formula:
// base_address + (y * line_length + x * bytes_per_pixel)
// Cast the address to an unsigned int pointer and set the color value
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
