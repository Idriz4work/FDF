/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 16:26:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Handle key events
int	key_presser(int key, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	ft_printf("Key pressed: %d\n", key);
	if (key == Z_KEY || key == X_KEY || key == Y_KEY || key == R_KEY)
		scaler(key, map);
	if (key == PLUS_KEY || key == MINUS_KEY)
		zoomer(key, map);
	if (key == ESC_KEY)
	{
		ft_printf("ESC pressed, exiting...\n");
		clean_exit(map, EXIT_SUCCESS);
	}
	else
		position_mover(key, map);
	redraw_window(map);
	return (0);
}

// Handle window close event
int	close_window(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	printf("Window closed. Exiting...\n");
	clean_exit(map, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

// Initialize the window and start the rendering
void	initialize_window(t_map *map)
{
	map->ptr_window_mlx = mlx_new_window(map->ptr_server_mlx, WIDTH, HEIGHT,
			"FDF");
	if (!map->ptr_window_mlx)
	{
		ft_printf("Failed to create window\n");
		clean_exit(map, EXIT_FAILURE);
		return ;
	}
	init_image(map);
	draw_wireframe(map);
	mlx_put_image_to_window(map->ptr_server_mlx, map->ptr_window_mlx,
		map->image, 0, 0);
	mlx_key_hook(map->ptr_window_mlx, key_presser, map);
	mlx_hook(map->ptr_window_mlx, 17, 0, close_window, map);
	ft_printf("Press ESC to exit, WASD to move, +/- to zoom.\n");
	mlx_loop(map->ptr_server_mlx);
	clean_exit(map, EXIT_SUCCESS);
}
