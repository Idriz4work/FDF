/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 02:32:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"


// Convert 3D to 2D with adjustable parameters
t_point dimension_change(int x, int y, int z, t_map *map)
{
    t_point result;
    
    // Apply z-scale to height values
    float scaled_z = z * map->z_scale;
    
    // Isometric projection calculation
    float iso_x = (x - y) * cos(ISO_ANGLE);
    float iso_y = (x + y) * sin(ISO_ANGLE) - scaled_z;
    
    // Apply scale and offset
    result.x = (int)(iso_x * map->scale) + (WIDTH / 2) + map->offset_x;
    result.y = (int)(iso_y * map->scale) + (HEIGHT / 2) + map->offset_y;
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
    int color = 0xFFFFFF; // Default color (white)
    
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            // Get height value
            int z = map->grid[y][x].z;
            
            // Color based on height (optional)
            if (z > 0)
                color = 0xFFFF00; // Yellow for peaks
            else if (z < 0)
                color = 0x0000FF; // Blue for valleys
            else
                color = 0xFFFFFF; // White for flat surfaces
                
            // Convert current 3D point to 2D
            current = dimension_change(x, y, z, map);
            
            // Draw line to right neighbor if it exists
            if (x < map->width - 1)
            {
                right = dimension_change(x + 1, y, map->grid[y][x + 1].z, map);
                draw_line(map, current, right, color);
            }
            
            // Draw line to bottom neighbor if it exists
            if (y < map->height - 1)
            {
                down = dimension_change(x, y + 1, map->grid[y + 1][x].z, map);
                draw_line(map, current, down, color);
            }
        }
    }
}
