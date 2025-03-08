/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 22:25:25 by iatilla-         ###   ########.fr       */
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

void	neighboring_box(int x, int y, t_map *map, int color, int decide)
{
	t_point	neighbor;
	t_point	current;

	current = dimension_change(x, y, map->grid[y][x].z, map);
	if (y < map->height - 1)
	{
		neighbor = dimension_change(x, y + 1, map->grid[y + 1][x].z, map);
		dda_draw_line(map, current, neighbor, color);
	}
	if (x < map->width - 1)
	{
		neighbor = dimension_change(x + 1, y, map->grid[y][x + 1].z, map);
		dda_draw_line(map, current, neighbor, color);
	}
}

// Draw the entire wireframe
void	draw_wireframe(t_map *map)
{
	int	y;
	int	x;
	int	z;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = color_decider(map->grid[y][x].z);
			neighboring_box(x, y, map, z, RIGHT);
			neighboring_box(x, y, map, z, DOWN);
			x++;
		}
		y++;
	}
}
