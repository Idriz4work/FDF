/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:05:22 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 15:05:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Initialize image for rendering
void	init_image(t_map *map)
{
	map->image = mlx_new_image(map->ptr_server_mlx, WIDTH, HEIGHT);
	map->addr = mlx_get_data_addr(map->image, &map->bits_per_pixel,
			&map->line_length, &map->endian);
}

// Initialize map values
void	init_map(t_map *map)
{
	map->offset_x = 0;
	map->offset_y = 0;
	map->scale = 30;
	map->z_scale = 1;
}

// Init structs with proper defaults
void	init_structs(t_map *map)
{
	map->ptr_server_mlx = NULL;
	map->ptr_window_mlx = NULL;
	map->offset_x = 0;
	map->offset_y = 0;
	map->scale = 1;
}
