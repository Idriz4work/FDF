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

void draw_line_dda(t_map *map, t_dst_cds *start, t_dst_cds *end)
{
    t_dda cord;
    int i;

    // Compute dx, dy
    cord.dx = end->x - start->x;
    cord.dy = end->y - start->y;

    // Determine steps
    cord.step = fabs(cord.dx) > fabs(cord.dy) ? fabs(cord.dx) : fabs(cord.dy);

    // Compute increments
    cord.x_inc = cord.dx / cord.step;
    cord.y_inc = cord.dy / cord.step;

    // Start drawing
    float x = start->x;
    float y = start->y;

    for (i = 0; i <= cord.step; i++)
    {
        mlx_pixel_put(map->ptr_server_mlx, map->ptr_window_mlx, round(x), round(y), 0x00FF00);
        x += cord.x_inc;
        y += cord.y_inc;
    }
}

// Convert 3D to 2D (Isometric Projection)
void isometric_projection(t_src *src, t_dst_cds *dest, float angle)
{
    float rad = angle * M_PI / 180; // Convert degrees to radians

    dest->x = (src->x_row - src->y_column) * cos(rad);
    dest->y = (src->x_row + src->y_column) * sin(rad) - src->z_value;
}


// this algorithm makes sure that we connect the points of the coordinates
// so that we can get an isometric projection (3D)
// we are going yo use DDA, its simpe and less compilacted
// void draw_line_dda(t_map *map, t_dst_cds *dest, t_src *src,int a)
// {

//     t_dda cord;

// 	int i,gd=DETECT,gm;

// 	if(dest->x>=dest->y)
// 		cord.step=dest->x;
// 	else
// 		cord.step=dest->y;

// 	dest->x=dest->x/cord.step;
// 	dest->y=dest->y/cord.step;

// 	x=x1;
// 	y=y1;

// 	i=1;
//     dest->x = src->x_row * cos(a) + src->y_column * cos(a + 2) + src->z_value * cos(a - 2);
//     dest->y = src->x_row * sin(a) + src->y_column * sin(a + 2) + src->z_value * sin(a - 2);
//     while(i<=step)
// 	{
// 		mlx_pixel_put(map->ptr_server_mlx,map->ptr_window_mlx,dest->x,dest->y,0x00FF00);
// 		dest->x=dest->x+dx;
// 		dest->y=dest->y+dy;
//         i++;
// 	}
// }

// this function draws the grid on the window
void draw_grid(t_map *map, int **grid, int rows, int cols)
{
    
}

