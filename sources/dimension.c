/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 01:55:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"


// Convert 3D to 2D (Isometric Projection)
t_point dimension_change(int x, int y, int z, t_map *map)
{
    t_point result;
    int scale = 30; // Scaling factor
    
    // Isometric projection calculation
    float iso_x = (x - y) * cos(ISO_ANGLE);
    float iso_y = (x + y) * sin(ISO_ANGLE) - z;
    
    // Set the image coordinates with scaling and offset
    result.x = (int)(iso_x * scale) + (WIDTH / 2);
    result.y = (int)(iso_y * scale) + (HEIGHT / 2);
    result.z = z;
    
    return result;
}

// Draw a line between two points using DDA algorithm
void draw_line(t_map *map, t_point start, t_point end, int color)
{
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    
    if (steps == 0)
        return;
        
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    
    float x = start.x;
    float y = start.y;
    
    for (int i = 0; i <= steps; i++)
    {
        put_pixel_to_image(map, round(x), round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

// Draw the entire wireframe
void draw_wireframe(t_map *map)
{
    t_point current;
    t_point right;
    t_point down;
    
    // Clear the image first (optional - set all pixels to black)
    ft_memset(map->addr, 0, WIDTH * HEIGHT * (map->bits_per_pixel / 8));
    
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            // Convert the current point from 3D to 2D
            current = dimension_change(x, y, map->grid[y][x].z, map);
            
            // Draw line to the right neighbor
            if (x < map->width - 1)
            {
                right = dimension_change(x + 1, y, map->grid[y][x + 1].z, map);
                draw_line(map, current, right, 0x00FF00);
            }
            
            // Draw line to the neighbor below
            if (y < map->height - 1)
            {
                down = dimension_change(x, y + 1, map->grid[y + 1][x].z, map);
                draw_line(map, current, down, 0x00FF00);
            }
        }
    }
}
