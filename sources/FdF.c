/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/09 16:50:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Populate map grid
int	map_prepare(char **split_line, t_map *map, int y)
{
	int	x;
	int	base;

	base = 0;
	x = 0;
	if (y == 0)
	{
		map->width = count_rows(split_line);
		if (map->width == 0)
			return (EXIT_FAILURE);
		map->grid = allocate_grid(map->width, map->height);
		if (!map->grid)
			return (EXIT_FAILURE);
	}
	if (y >= map->height)
		return (EXIT_FAILURE);
	while (split_line[x] && x < map->width)
	{
		base = detect_base(split_line[x]);
		map->grid[y][x].x = x;
		map->grid[y][x].y = y;
		map->grid[y][x].z = ft_atoi_hex(split_line[x], base);
		x++;
	}
	return (EXIT_SUCCESS);
}

int	process_rows(t_map *map, int fd)
{
	int		y;
	char	**split_line;
	int		len;
	char	*line;

	y = 0;
	while ((line = get_next_line(fd)) && y < map->height)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		split_line = ft_split(line, ' ');
		if (!split_line || map_prepare(split_line, map, y) == EXIT_FAILURE)
		{
			free_array((void **)split_line);
			free(line);
			close(fd);
			
			return (EXIT_FAILURE);
		}
		free_array((void **)split_line);
		free(line);
		y++;
	}
	close(fd);
	return (EXIT_SUCCESS);
}

// Read file and process content
int	scan_file(t_map *map, const char *file)
{
	int		fd;
	int		line_count;
	char	*line;

	line_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		clean_up(map);
		return (EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)))
	{
		line_count++;
		free(line);
	}
	map->height = line_count;
	close(fd);
	return (EXIT_SUCCESS);
}

// Cleans up the map before return
void clean_up(t_map *map)
{
	int i = 0;
    if (!map)
        return;
    if (map->grid)
       free_array((void **)map->grid);
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


// Main entry point
int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	if (argc != 2)
	{
		ft_printf("Usage: %s <filename>.fdf\n", argv[0]);
		return (EXIT_FAILURE);
	}
	map.ptr_server_mlx = mlx_init();
	if (!map.ptr_server_mlx)
		return (EXIT_FAILURE);
	if (scan_file(&map, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || map.height == 0)
	{
		clean_up(&map);
		return (EXIT_FAILURE);
	}
	if (process_rows(&map, fd) == EXIT_FAILURE)
	{
		clean_up(&map);
		ft_printf("Failed process rows\n");
		return (EXIT_FAILURE);
	}
	initialize_window(&map);
	return (EXIT_SUCCESS);
}
