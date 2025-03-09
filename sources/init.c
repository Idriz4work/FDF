/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:05:22 by marvin            #+#    #+#             */
/*   Updated: 2025/03/09 22:50:30 by iatilla-         ###   ########.fr       */
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
	if (!map)
		return ;
	map->ptr_server_mlx = NULL;
	map->ptr_window_mlx = NULL;
	map->grid = NULL;
	map->image = NULL;
	map->addr = NULL;
	map->width = 0;
	map->height = 0;
	map->bits_per_pixel = 0;
	map->line_length = 0;
	map->endian = 0;
	map->offset_x = 0;
	map->offset_y = 0;
	map->scale = 10;
	map->z_scale = 1;
}
