/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/02/24 00:03:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// this algorithm makes sure that we connect the points of the coordinates
// so that we can get an isometric projection (3D)
// we are going yo use DDA, its simpe and less compilacted
void	draw_line_dda(t_map *map, t_img *start, t_src *end)
{
	// t_dda cord;
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
		round(y), 0x00FF00);
		//     x += cord.x_inc;
		//     y += cord.y_inc;
		// }
}

// Convert 3D to 2D (Isometric Projection)
// Convert degrees to radians
void	dimension_changer(t_src *three_d, t_img *two_d, int angle)
{
	float	rad;

	rad = 0;
	rad = angle * M_PI / 180;
	two_d->x = (three_d->x_row - three_d->y_column) * cos(rad);
	two_d->y = (three_d->x_row + three_d->y_column) * sin(rad)
		- three_d->z_value;
}
