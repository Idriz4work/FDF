/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_spawner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:27 by marvin            #+#    #+#             */
/*   Updated: 2025/03/09 17:38:49 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Count the number of columns in the map
int	count_columns(char **split_line)
{
	int	count;

	count = 0;
	while (split_line[count])
		count++;
	return (count);
}

// Count the number of rows in the map
int	count_rows(char **lines)
{
	int	rows;

	rows = 0;
	while (lines[rows])
		rows++;
	return (rows);
}

// Correctly allocate 2D grid
t_point	**allocate_grid(int width, int height)
{
	t_point	**grid;
	int		i;

	grid = malloc(sizeof(t_point *) * height);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = malloc(sizeof(t_point) * width);
		if (!grid[i])
		{
			free_array((void *)grid, i);
			return (NULL);
		}
		i++;
	}
	return (grid);
}
