/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_height_increase.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:26:53 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/10 16:27:12 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// fucntion that can change height
// Static variable to preserve value between function calls
// Save the original scale value only once at the beginning
void	scaler(int key, t_map *map)
{
	static float	original_scale = 0;

	if (original_scale == 0)
		original_scale = map->z_scale;
	ft_printf("Scaler: %i", key);
	if (key == Z_KEY)
		map->z_scale += 1;
	else if (key == Y_KEY)
		map->z_scale -= 1;
	else if (key == X_KEY)
		map->z_scale = 0;
	else if (key == R_KEY)
		map->z_scale = original_scale;
}
