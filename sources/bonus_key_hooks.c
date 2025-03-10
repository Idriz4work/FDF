/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_key_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:05:41 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 16:13:03 by iatilla-         ###   ########.fr       */
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

//
void	position_mover(int key, t_map *map)
{
	if (key == A_KEY)
		map->offset_x += 10;
	else if (key == D_KEY)
		map->offset_x -= 10;
	else if (key == W_KEY)
		map->offset_y -= 10;
	else if (key == S_KEY)
		map->offset_y += 10;
}

//
void	zoomer(int key, t_map *map)
{
	if (key == PLUS_KEY)
		map->scale += 2;
	else if (key == MINUS_KEY)
	{
		if (map->scale > 2)
			map->scale = map->scale - 2;
		else
			map->scale = map->scale;
	}
}
