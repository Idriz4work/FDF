/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 19:17:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Convert 3D to 2D with adjustable parameters
// Apply z-scale to height values
// Isometric projection calculation
// Apply scale and offset
t_point	dimension_change(int x, int y, int z, t_map *map)
{
	t_point	result;
	float	scaled_z;
	float	iso_x;
	float	iso_y;

	scaled_z = z * map->z_scale;
	iso_x = (x - y) * cos(ISO_ANGLE);
	iso_y = (x + y) * sin(ISO_ANGLE) - scaled_z;
	result.x = (int)(iso_x * map->scale) + (WIDTH / 2) + map->offset_x;
	result.y = (int)(iso_y * map->scale) + (HEIGHT / 2) + map->offset_y;
	result.z = z;
	return (result);
}

// Draw a line between two points using DDA algorithm
void	draw_line(t_map *map, t_point start, t_point end, int color)
{
	t_dda	dda;

	dda.dx = end.x - start.x;
	dda.dy = end.y - start.y;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.steps = fabs(dda.dx);
	else if (fabs(dda.dx) > fabs(dda.dy))
		dda.steps = fabs(dda.dy);
	if (dda.steps == 0)
		return ;
	dda.x_inc = dda.dx / dda.steps;
	dda.y_inc = dda.dy / dda.steps;
	dda.x = start.x;
	dda.y = start.y;
	dda.i = 0;
	while (dda.i <= dda.steps)
	{
		put_pixel_to_image(map, round(dda.x), round(dda.y), color);
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
		dda.i++;
	}
}

// Color based on height
int	decide_color(int z)
{
    int color  = 0xFFFFFF;
	if (z > 0)
		color = get_trgb(0, 45, 12, 80);
        else if (z < 0)
		color = get_trgb(0, 45, 12, 80);
        else
		color = get_trgb(0, 45, 12, 80);
        return color;
}
    
// Draw line to right neighbor if it exists
// Get the z-value of the right neighbor from the grid
// Convert the 3D coordinates of the right neighbor to 2D
// Determine the color based on the right neighbor's z-value
// Draw a line from the current 2D point to the right neighbor's 2D point
void	neighbor_draw(t_point right, t_map *map, int z, t_point current)
{
    if (right.x < map->width)
        ft_printf("right doesnt exist");
    right.z = map->z_scale;
    right = dimension_change(right.x,right.y,right.z,map);
    
    draw_line(map,current,right,z);
}
    
/*Verify that the bottom neighbor exists (check if down.y < map->height)
If it doesn't exist, simply return without drawing anything


Drawing the Connection:

If the bottom neighbor exists:

Get the z-value of the bottom neighbor from the grid
Convert the 3D coordinates of the bottom neighbor to 2D
Determine the color based on the bottom neighbor's z-value
Draw a line from the current 2D point to the bottom neighbor's 2D poin
*/
void	neighbor_draw_down(t_point down, t_map *map, int z, t_point current)
{
    if (down.x < map->width)
        ft_printf("down doesnt exist");
}

// Set up right neighbor coordinates
// Set up bottom neighbor coordinates
void setup_cords(t_point *right, t_point *down, t_point tmp)
{
    right->x = tmp.x + 1;
    right->y = tmp.y;
    down->x = tmp.x;
    down->y = tmp.y + 1;
}

// Draw the entire wireframe
// Get height value
// Convert current 3D point to 2D
void	draw_wireframe(t_map *map)
{
	t_point	current;
	t_point	right;
	t_point	down;
    t_point tmp;
	int		color;

	color = 0xFFFFFF;
	tmp.y = 0;
	tmp.x = 0;
	while (tmp.y < map->height)
	{
		while (tmp.x < map->width)
		{
			tmp.z = map->grid[tmp.y][tmp.x].z;
			color = decide_color(tmp.z);
			current = dimension_change(tmp.x, tmp.y, tmp.z, map);
            setup_cords(&right,&down,tmp);
			neighbor_draw(right, map, tmp.z, current);
			neighbor_draw_down(down, map, tmp.z, current);
			tmp.x++;
		}
		tmp.y++;
	}
}
