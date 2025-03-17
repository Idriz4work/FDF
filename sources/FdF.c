/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/02 01:17:30 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Convert 3D coordinates to isometric projection
t_two_d	iso_projection(float x, float y, float z)
{
	t_two_d	iso;

	// Isometric formulas
	iso.x = (x - y) * cos(ISO_ANGLE);
	iso.y = (x + y) * sin(ISO_ANGLE) - z;
	// Center the projection
	iso.x += 400; // Half of window width
	iso.y += 300; // Adjust for better viewing
	return (iso);
}

void	three_d_two_d(void)
{
}

void	allocate_grid(t_map *map, int rows, int cols)
{
	int	i;

	i = 0;
	map->grid = malloc(sizeof(char *) * rows);
	if (map->grid == NULL)
	{
		perror("Failed to allocate memory for grid rows");
		exit(EXIT_FAILURE);
	}
	while (i < rows)
	{
		map->grid[i] = malloc(sizeof(char) * (cols + 1));
		if (map->grid[i] == NULL)
		{
			perror("Failed to allocate memory for grid columns");
			exit(EXIT_FAILURE);
		}
	}
}

// this function fills the grid with the values into
// a 2D value grid
size_t	get_column_size(char *row)
{
	size_t	i;
	size_t	max_cols;
	int		line_len;

	i = 0;
	max_cols = 0;
	while (row[i] != '\0')
	{
		line_len = ft_strlen(row);
		if (line_len > max_cols)
			max_cols = line_len;
		i++;
	}
	return (max_cols);
}

void	place_values(t_map *map, t_three_d *cords)
{
}

int	read_input(char **argv, t_map *map, t_three_d *cords, t_two_d *cords_two)
{
	char	**lines;
	int		fd;

	fd = open(argv[1], "OR_RD");
	if (fd == -1)
	{
		strerror("error opening file\n");
		exit(-1);
	}
	while (lines[cords->xrow] != NULL)
	{
		lines[cords->xrow] = get_next_line(fd);
		cords->ycol = get_column_size(lines);
		cords->xrow++;
	}
	allocate_grid(map, cords->xrow, cords->ycol);
	three_d_two_d(map, lines, cords, &cords_two);
	// Cleanup
	close(fd);
	return (0);
}

char **scan_file(int file, t_src *src_points)
{
    char **lines = (char **)malloc(sizeof(char *) * 4096);
    if (lines == NULL)
    {
        perror("ERROR with alocating size for lines\n");
        return NULL;
    }
    while (lines[i] != NULL)
    {
        lines[i] = get_next_line(file);
        src_points->x_row++;
        src_points->y_column = count_column(ft_split(lines[i],' '));
        src_points->x_row = asign_heigth(ft_split(lines[i],' '));
        i++;
    }
    return lines;
}

void	initialize_window(t_map *map, t_three_d *cords_three,
		t_two_d *cords_two)
{
	map->ptr_server_mlx = mlx_init();
	if (!map->ptr_server_mlx)
	{
		ft_putstr_fd("Error: failed to set up server\n", 2);
		exit(-1);
	}
	map->ptr_window_mlx = mlx_new_window(map->ptr_server_mlx, 1200, 1200,
			"FdF");
	if (!map->ptr_window_mlx)
	{
		ft_putstr_fd("Error: failed to create window\n", 2);
		mlx_destroy_display(map->ptr_server_mlx);
		free(map->ptr_server_mlx);
		exit(-1);
	}
	// Draw the grid
	draw_grid(map, map->grid, cords_two->x, cords_two->y);
	// mlx_key_hook(map->ptr_window_mlx, key_handler, map);
	// mlx_hook(map->ptr_window_mlx, 17, 0, close_window, map);
	mlx_loop(map->ptr_server_mlx);
}

void	init_structs(t_two_d *dest_cds, t_three_d *three_d_cds)
{
	dest_cds->x = 0;
	dest_cds->y = 0;
	three_d_cds->xrow = 0;
	three_d_cds->ycol = 0;
	three_d_cds->zval = 0;
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_three_d	cords;
	t_two_d		cords_two;

	if (argc != 2)
	{
		ft_printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	if (read_input(argv, &map, &cords, &cords_two) == -1)
	{
		strerror("failed to read input: ", argv[1]);
		exit(-1);
	}
	// put values into their 2D place
	place_values(&map, &cords_two);
	initialize_window(&map, &cords, &cords_two);
	// Draw the grid
	draw_grid(&map, &map.grid, &cords.xrow, &cords.ycol);
	return (0);
}
