/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 17:34:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Function to redraw the entire window with updated position
void	redraw_window(t_map *map)
{
	ft_memset(map->addr, 0, WIDTH * HEIGHT * (map->bits_per_pixel / 8));
	draw_wireframe(map);
	mlx_put_image_to_window(map->ptr_server_mlx, map->ptr_window_mlx,
		map->image, 0, 0);
}

void	position_mover(int key, t_map *map, void *param)
{
	if (key == A_KEY)
		map->offset_x += 10;
	else if (key == D_KEY)
		map->offset_x -= 10;
	else if (key == W_KEY)
		map->offset_y += 10;
	else if (key == S_KEY)
		map->offset_y -= 10;
}

void	zoomer(int key, t_map *map, void *param)
{
	if (key == PLUS_KEY)
		map->scale += 2;
	else if (key == MINUS_KEY)
		map->scale = (map->scale > 2) ? map->scale - 2 : map->scale;
}

void	scaler(int key, t_map *map, void *param)
{
	if (key == Z_KEY)
		map->z_scale += 0.1;
	else if (key == X_KEY)
	{
		if ((map->z_scale > 0.1))
			map->z_scale = map->z_scale;
		else
			map->z_scale = map->z_scale;
	}
}

// Handle key events
int	key_presser(int key, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	ft_printf("Key pressed: %d\n", key);
	if (key == Z_KEY || key == X_KEY)
		scaler(key,map, param);
	else if (key == PLUS_KEY || key == MINUS_KEY)
		zoomer(key, map, param);
    else if (key == ESC_KEY)
    {
        ft_printf("ESC pressed, exiting...\n");
        mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
        exit(EXIT_SUCCESS);
    }
	else
		position_mover(key, map, param);
	redraw_window(map);
	return (0);
}

// Handle window close event
int	close_window(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	printf("Window closed. Exiting...\n");
	mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

// Initialize the window and start the rendering
void	initialize_window(t_map *map)
{
	init_map(map);
	map->ptr_window_mlx = mlx_new_window(map->ptr_server_mlx, WIDTH, HEIGHT,
			"FDF");
	if (!map->ptr_window_mlx)
	{
		ft_printf("Failed to create window\n");
		return ;
	}
	init_image(map);
	draw_wireframe(map);
	mlx_put_image_to_window(map->ptr_server_mlx, map->ptr_window_mlx,
		map->image, 0, 0);
	mlx_key_hook(map->ptr_window_mlx, key_presser, map);
	mlx_hook(map->ptr_window_mlx, 17, 0, close_window, map);
	ft_printf("Window initialized. Press ESC to exit, WASD to move,+/- to zoom.\n");
	mlx_loop(map->ptr_server_mlx);
}
