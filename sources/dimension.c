/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 03:29:45 by iatilla-         ###   ########.fr       */
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
	result.x = iso_x * map->scale + (WIDTH / 2) + map->offset_x;
	result.y = iso_y * map->scale + (HEIGHT / 2) + map->offset_y;
	result.z = z;
	return (result);
}
// Draw line to right neighbor if it exists
// Get the z-value of the right neighbor from the grid
// Convert the 3D coordinates of the right neighbor to 2D
// Determine the color based on the right neighbor's z-value
// Draw a line from the current 2D point to the right neighbor's 2D point
void	neighbor_draw_right(t_point right, t_map *map, t_point current)
{
	int		color;
	t_point	right_two_d;

	if (right.x >= map->width || right.y >= map->height)
		return ;
	right.z = map->grid[right.y][right.x].z;
	color = right.z;
	right_two_d = dimension_change(right.x, right.y, right.z, map);
	draw_line(map, current, right_two_d, color);
}

/*Verify that the bottom neighbor exists (check if down.y < map->height)
	If it doesn't exist, simply return without drawing anything


	Drawing the Connection:

	If the bottom neighbor exists:

	Get the z-value of the bottom neighbor from the grid
	Convert the 3D coordinates of the bottom neighbor to 2D
	Determine the color based on the bottom neighbor's z-value
	Draw a line from the current 2D point to the bottom neighbor's 2D point
*/
void	neighbor_draw_down(t_point down, t_map *map, t_point current)
{
	int		color;
	t_point	down_two_d;

	if (down.x >= map->width || down.y >= map->height)
		return ;
	down.z = map->grid[down.y][down.x].z;
	color = down.z;
	down_two_d = dimension_change(down.x, down.y, down.z, map);
	draw_line(map, current, down_two_d, color);
}

// Set up right neighbor coordinates
// do that via incrementing the x val for tmp;
// Set up bottom neighbor coordinates
// do that by increment the y value for tmp
void	setup_cords(t_point *right, t_point *down, t_point tmp, t_map *map)
{
	right->x = tmp.x + 1;
	right->y = tmp.y;
	down->x = tmp.x;
	down->y = tmp.y + 1;
}

// Draw the entire wireframe
// Get height value
// Convert current 3D point to 2D
// draw lines neighbor right and neighbor down
void	draw_wireframe(t_map *map)
{
	t_point	current;
	t_point	right;
	t_point	down;
	t_point	tmp;

	tmp.y = 0;
	while (tmp.y < map->height)
	{
		tmp.x = 0;
		while (tmp.x < map->width)
		{
			tmp.z = map->grid[tmp.y][tmp.x].z;
			current = dimension_change(tmp.x, tmp.y, tmp.z, map);
			setup_cords(&right, &down, tmp, map);
			neighbor_draw_right(right, map, current);
			neighbor_draw_down(down, map, current);
			tmp.x++;
		}
		tmp.y++;
	}
}
