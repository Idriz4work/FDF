/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_connecter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:40 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 17:30:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Create a color value from individual RGBA components
int	get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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
