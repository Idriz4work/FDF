/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:03:27 by marvin            #+#    #+#             */
/*   Updated: 2025/02/24 00:03:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

map->grid = grid_allocater();
if(map->grid == NULL)
{
    free_array((void **)map->grid);
    ft_printf("ERROR IN GRID ALLOCATE INIT STRUCT\n");
    exit(EXIT_FAILURE);
}
