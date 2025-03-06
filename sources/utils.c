/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:44:47 by marvin            #+#    #+#             */
/*   Updated: 2025/03/06 01:04:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// frees the array and sets it to null
void	free_array(void **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	grid = NULL;
}

void	init_structs(t_img *dest_cds, t_point *three_d_cds)
{
	dest_cds->x = 0;
	dest_cds->y = 0;
	dest_cds->bits_per_pixel = 0;
	dest_cds->line_length = 0;
	dest_cds->endian = 0;
	three_d_cds->x = 0;
	three_d_cds->y = 0;
	three_d_cds->z = 0;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

