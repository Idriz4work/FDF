/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_increase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:25:04 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/09 23:16:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Linear interpolation between two values
float	lerp(float start, float end, float t)
{
	return (start + t * (end - start));
}

// Apply linear interpolation to each color channel
// Ensure values stay within 0-255 range
t_rgb	color_lerp(t_rgb color1, t_rgb color2, float t)
{
	t_rgb	result;

	result.red = (int)lerp((float)color1.red, (float)color2.red, t);
	result.green = (int)lerp((float)color1.green, (float)color2.green, t);
	result.blue = (int)lerp((float)color1.blue, (float)color2.blue, t);
	if (result.red > 255)
		result.red = 255;
	else if (result.red < 0)
		result.red = 0;
	if (result.green > 255)
		result.green = 255;
	else if (result.green < 0)
		result.green = 0;
	if (result.blue > 255)
		result.blue = 255;
	else if (result.blue < 0)
		result.blue = 0;
	return (result);
}

// Convert RGB color to integer representation
int	rgb_to_int(t_rgb color)
{
	return ((color.red << 16) | (color.green << 8) | color.blue);
}

// Example usage for wireframe coloring with two colors
int	calculate_gradient_color(t_point p1, t_point p2, float z_value)
{
	float	t;
	float	z_min;
	float	z_max;
	t_rgb	start_color;
	t_rgb	end_color;

	z_min = (float)fmin(p1.z, p2.z);
	z_max = (float)fmax(p1.z, p2.z);
	if (z_max == z_min)
		t = 0.5f;
	else
		t = (z_value - z_min) / (z_max - z_min);
	start_color.red = 255;
	start_color.green = 0;
	start_color.blue = 0;
	end_color.red = 255;
	end_color.green = 255;
	end_color.blue = 255;
	end_color = color_lerp(start_color, end_color, t);
	return (rgb_to_int(end_color));
}
