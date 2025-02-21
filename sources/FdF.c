/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/01/15 22:05:32 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Convert 3D coordinates to isometric projection
t_coord iso_projection(float x, float y, float z)
{
    t_coord iso;
    // Isometric formulas
    iso.x = (x - y) * cos(ISO_ANGLE);
    iso.y = (x + y) * sin(ISO_ANGLE) - z;
    
    // Center the projection
    iso.x += 400;  // Half of window width
    iso.y += 300;  // Adjust for better viewing
    return iso;
}

int read_input(char *filename, t_map *map)
{
    char **lines;
    int row_size = 0;
    int fd = open(argv[1],"OR_RD");
    if (fd == -1)
    {
        strerror("error opening file\n");
        exit(-1);
    }
    while (lines[row_size] != NULL)
    {
        lines[row_size] = get_next_line(fd);
        row_size++;
    }
    map->grid = allocate_grid(row_size,column_size);
    // Draw the grid
    draw_grid(map, map->grid, row_size, column_size);
    // Cleanup
    free_array(grid);
    free(grid);
    close(fd);
    return 0;
}

void initialize_window(t_map *map, char *argv)
{
    map->ptr_server_mlx = mlx_init();
    if (!map->ptr_server_mlx)
    {
        strerror("failed to set up server: ",map->ptr_server_mlx);
        exit(-1);
    }
    map->ptr_window_mlx = mlx_new_window(map->ptr_server_mlx, 1200, 1200, "FdF");
    if (!map->ptr_window_mlx)
    {
        mlx_destroy_window(map->ptr_server_mlx, map->ptr_window_mlx);
        strerror("failed to set up server: ",map->ptr_server_mlx);
        exit(-1);
    }
    if (read_input(argv, map) == -1)
    {
        strerror("failed to read input: ",argv[1]);
        exit(-1);
    }
    mlx_loop(map->ptr_server_mlx);
}

int main(int argc, char **argv)
{
    t_map map;
    
    if (argc != 2)
    {
        ft_printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    initialize_window(&map, argv[1]);

    return 0;
}
