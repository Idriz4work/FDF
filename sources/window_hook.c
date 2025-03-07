/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 01:59:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Initialize the image
void    init_image(t_map *map)
{
    map->image = mlx_new_image(map->ptr_server_mlx, WIDTH, HEIGHT);
    map->addr = mlx_get_data_addr(map->image, &map->bits_per_pixel,
            &map->line_length, &map->endian);
}

// Handle key events
int key_presser(int key, t_map *map)
{
    if (key == ESC_KEY)
    {
        printf("Key %d pressed. Exiting...\n", key);
        mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
        exit(EXIT_SUCCESS);
    }
    if (key == A_KEY)
        map->offset_x -= 10;
    if (key == S_KEY)
        map->offset_y += 10;
    if (key == D_KEY)
        map->offset_x += 10;
    if (key == W_KEY)
        map->offset_y -= 10;
    return (0);
}

// Handle window close event
int close_window(t_map *map)
{
    printf("Window closed. Exiting...\n");
    mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
    exit(EXIT_SUCCESS);
    return (0);
}

// Initialize the window and start the rendering
void initialize_window(t_map *map)
{
    map->ptr_window_mlx = mlx_new_window(map->ptr_server_mlx, WIDTH, HEIGHT, "FDF");
    if (!map->ptr_window_mlx)
        return;
    
    // Initialize the image
    init_image(map);
    
    // Draw the wireframe
    draw_wireframe(map);
    
    // Put the image to the window
    mlx_put_image_to_window(map->ptr_server_mlx, map->ptr_window_mlx, map->image, 0, 0);
    
    // Set up event hooks if needed
    mlx_key_hook(map->ptr_window_mlx, key_presser, map);
    mlx_hook(map->ptr_window_mlx, 17, 0, close_window, map);
    
    mlx_loop(map->ptr_server_mlx);
}