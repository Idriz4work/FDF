/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/06 00:04:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Convert 3D to 2D (Isometric Projection)
// Convert degrees to radians
void	dimension_change(t_point *point, int scale, t_img *img)
{
	int	x;
	int	y;
	int	z;

	x = point->x;
	y = point->y;
	z = point->z;
	img->x = (x - y) * cos(ISO_ANGLE) * scale;
	img->y = (x + y) * sin(ISO_ANGLE) * scale - z * scale;
}


// this algorithm makes sure that we connect the points of the coordinates
// so that we can get an isometric projection (3D)
// we are going yo use DDA, its simpe and less compilacted
void	draw_line_dda(t_map *map, t_img *start, t_point *end)
{
	// int i;
	// // Compute dx, dy
	// cord.dx = end->x - start->x;
	// cord.dy = end->y - start->y;
	// // Determine steps
	// cord.step = fabs(cord.dx) > fabs(cord.dy) ? fabs(cord.dx) : fabs(cord.dy);
	// // Compute increments
	// cord.x_inc = cord.dx / cord.step;
	// cord.y_inc = cord.dy / cord.step;
	// // Start drawing
	// float x = start->x;
	// float y = start->y;
	// for (i = 0; i <= cord.step; i++)
	// {
	//     mlx_pixel_put(map->ptr_server_mlx, map->ptr_window_mlx, round(x),
		// round(y), 0x00FF00);
		//     x += cord.x_inc;
		//     y += cord.y_inc;
		// }
}
