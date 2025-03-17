/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:14 by iatilla-          #+#    #+#             */
/*   Updated: 2025/02/24 22:59:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// frees the array and sets it to null
void free_array(void **grid)
{
    int i = 0;
    while (grid[i] != NULL)
    {
        free(grid[i]);
        i++;
    }
    free(grid);
    grid = NULL;
}
