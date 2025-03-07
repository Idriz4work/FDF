/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:44:47 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 02:13:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Frees the array and sets it to NULL
void free_array(void **array)
{
    int i;

    if (!array)
        return;
    
    for (i = 0; array[i]; i++)
        free(array[i]);
    free(array);
    array = NULL;
}

// Init structs with proper defaults
void init_structs(t_map *map)
{
    map->ptr_server_mlx = NULL;
    map->ptr_window_mlx = NULL;
    map->offset_x = 0;
    map->offset_y = 0;
    map->scale = 1;
}

// Create a color value from individual RGBA components
int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

// Count the number of columns in the map
int count_columns(char **split_line)
{
    int count = 0;

    while (split_line[count])
        count++;
        
    return count;
}

// Count the number of rows in the map
int count_rows(char **lines)
{
    int rows = 0;
    while (lines[rows])
        rows++;
    return rows;
}
