/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:30:20 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/09 22:55:56 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Determine the number of steps
// Calculate increments
// Starting position
void	dda_draw_line(t_map *map, t_point start, t_point end, int color)
{
	t_dda	dda;

	dda.dx = end.x - start.x;
	dda.dy = end.y - start.y;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.steps = fabs(dda.dx);
	else
		dda.steps = fabs(dda.dy);
	if (dda.steps == 0)
		return ;
	dda.x_inc = dda.dx / dda.steps;
	dda.y_inc = dda.dy / dda.steps;
	dda.x = start.x;
	dda.y = start.y;
	dda.i = 0;
	while (dda.i <= dda.steps)
	{
		put_pixel_to_image(map, round(dda.x), round(dda.y), color);
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
		dda.i++;
	}
}
