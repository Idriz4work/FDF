/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_color_increase.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:25:04 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/08 22:45:02 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Change the color in each step
// Lighten by 1 unit in RGB space
// Darken by 1 unit in RGB space
// Loop until the number of steps is equal to abs(z)
int	shader(int z, int color)
{
	int	i;
	int	radient;

	i = 0;
	if (z > 0)
		radient = 1;
	else
		radient = -1;
	while (i != abs(z))
	{
		if (radient == 1)
			color += 0x010101;
		else
			color -= 0x010101;
		i++;
	}
	return (color);
}

int	color_decider(int z)
{
	int	color;

	if (z < -10)
		color = 0x35206e;
	else if (z < 0)
		color = 0x501ae1;
	else if (z == 0)
		color = 0xFFFFFF;
	else if (z >= 1)
		color = 0xec5942;
	if (z >= 3)
		color = 0xcf3a23;
	if (z >= 5)
		color = 0xc6280f;
	else if (z >= 10)
		color = 0x9e0000;
	else
		color = 0xf04a4a;
	color = shader(z, color);
	return (color);
}
