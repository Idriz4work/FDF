/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/06 00:54:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	key_presser(int key, t_map *map)
{
	if (key == ESC_KEY)
	{
		printf("Key %d pressed. Exiting...\n", key);
		mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
		exit(EXIT_SUCCESS);
	}
	if (key == A_KEY)
		move_position_left();
	if (key == S_KEY)
		move_position_down();
	if (key == D_KEY)
		move_position_right();
	if (key == W_KEY)
		move_position_up();
	return (0);
}

int	handle_x(t_map *map)
{
	printf("Window closed. Exiting...\n");
	mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

// Initialize the window
void	initialize_window(t_map *map, t_img *dest, t_point *src)
{
	map->ptr_window_mlx = mlx_new_window(map->ptr_server_mlx, 1200, 1200,
			"FdF");
	if (!map->ptr_window_mlx)
	{
		mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
		perror("Failed to set up window");
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(map->ptr_server_mlx, key_presser, map);
	mlx_hook(map->ptr_window_mlx, 17, 0, handle_x, map);
	mlx_loop(map->ptr_server_mlx);
}
