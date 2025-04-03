/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:10:46 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/09 17:37:50 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// free function for split values
void	free_splitter(void **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// free function for arrays but with their size as condition
void	free_array(void **array, int size)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// Utility function to clean up and exit
void	clean_exit(t_map *map, int status)
{
	if (map->image)
		mlx_destroy_image(map->ptr_server_mlx, map->image);
	if (map->ptr_window_mlx)
		mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
	if (map->grid)
		free_array((void **)map->grid, map->height);
	exit(status);
}

// Cleans up the map before return
void	clean_up(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (map->grid)
		free_array((void **)map->grid, map->height);
	if (map->image)
		free(map->image);
	if (map->addr)
		free(map->addr);
	if (map->ptr_window_mlx)
		free(map->ptr_window_mlx);
	if (map->ptr_server_mlx)
		free(map->ptr_server_mlx);
	map->grid = NULL;
	map->image = NULL;
	map->addr = NULL;
	map->ptr_window_mlx = NULL;
	map->ptr_server_mlx = NULL;
}
