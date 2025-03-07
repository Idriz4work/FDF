/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:44:47 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 03:09:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// RETURNS THE BASE 
int detect_base(const char *input) {
    if (input[0] == '0' && (input[1] == 'x' || input[1] == 'X'))
        return 16;
    return 10;
}

// ft_atoi_hex helper
int convert_helper(const char *input, int numeral_base)
{
    int result = 0;
    while ((*input >= '0' && *input <= '9') || (*input >= 'a' && *input <= 'a' + numeral_base - 10))
    {
        if (*input >= '0' && *input <= '9')
            result = result * numeral_base + *input++ - '0';
        else
            result = result * numeral_base + *input++ - 'a' + 10;
    }
    return result;
}

int ft_atoi_hex(const char *input, int base)
{
    int result = 0;
    int sign_multiplier = 1;

    while (*input == ' ' || *input == '\t' || *input == '\n' || *input == '\v' || *input == '\f' || *input == '\r')
        input++;
    
    if (*input == '+' || *input == '-')
    {   
        if (*input == '-')
        
            sign_multiplier *= -1;
        
        input++;
    }
    
    if (base <= 10)
    {
        while (*input >= '0' && *input <= '0' + base)
            result = result * base + *input++ - '0';
        return result * sign_multiplier;
    }
    else
    
        return convert_helper(input, base) * sign_multiplier;
    
}


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
