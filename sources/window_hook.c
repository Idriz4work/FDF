/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 03:12:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Initialize image for rendering
void init_image(t_map *map)
{
    map->image = mlx_new_image(map->ptr_server_mlx, WIDTH, HEIGHT);
    map->addr = mlx_get_data_addr(map->image, &map->bits_per_pixel,
            &map->line_length, &map->endian);
}

// Initialize map values
void init_map(t_map *map)
{
    map->offset_x = 0;
    map->offset_y = 0;
    map->scale = 30;  
    map->z_scale = 1; 
}

// Function to redraw the entire window with updated position
void redraw_window(t_map *map)
{
    ft_memset(map->addr, 0, WIDTH * HEIGHT * (map->bits_per_pixel / 8));
    draw_wireframe(map);
    mlx_put_image_to_window(map->ptr_server_mlx, map->ptr_window_mlx, map->image, 0, 0);
}

// Handle key events
int key_presser(int key, void *param)
{
    t_map *map = (t_map *)param;
    
    printf("Key pressed: %d\n", key);
    
    if (key == A_KEY)
        map->offset_x += 10;
    else if (key == D_KEY)
        map->offset_x -= 10;
    else if (key == W_KEY)
        map->offset_y += 10;
    else if (key == S_KEY)
        map->offset_y -= 10;
    else if (key == PLUS_KEY)
        map->scale += 2;
    else if (key == MINUS_KEY)
        map->scale = (map->scale > 2) ? map->scale - 2 : map->scale;
    else if (key == Z_KEY)
        map->z_scale += 0.1;
    else if (key == X_KEY)
        map->z_scale = (map->z_scale > 0.1) ? map->z_scale - 0.1 : map->z_scale;
    else if (key == ESC_KEY)
    {
        printf("ESC pressed, exiting...\n");
        mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
        exit(EXIT_SUCCESS);
    }
    
    redraw_window(map);
    
    return (0);
}

// Handle window close event
int close_window(void *param)
{
    t_map *map = (t_map *)param;
    
    printf("Window closed. Exiting...\n");
    mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
    exit(EXIT_SUCCESS);
    return (0);
}

// Initialize the window and start the rendering
void initialize_window(t_map *map)
{
    init_map(map);
    
    map->ptr_window_mlx = mlx_new_window(map->ptr_server_mlx, WIDTH, HEIGHT, "FDF");
    if (!map->ptr_window_mlx)
    {
        printf("Failed to create window\n");
        return;
    }
    
    init_image(map);
    draw_wireframe(map);
    mlx_put_image_to_window(map->ptr_server_mlx, map->ptr_window_mlx, map->image, 0, 0);
    
    mlx_key_hook(map->ptr_window_mlx, key_presser, map);
    mlx_hook(map->ptr_window_mlx, 17, 0, close_window, map);
    
    printf("Window initialized. Press ESC to exit, WASD to move, +/- to zoom.\n");
    
    mlx_loop(map->ptr_server_mlx);
}
