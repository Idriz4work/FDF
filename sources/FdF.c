/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/07 17:40:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// Populate map grid
int	map_prepare(char **split_line, t_map *map, int y, t_point *src)
{
	int	x;

	x = 0;
	if (y == 0)
	{
		map->width = count_columns(split_line);
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
		map->grid[y][x].x = x;
		map->grid[y][x].y = y;
		map->grid[y][x].z = ft_atoi_hex(split_line[x],
				detect_base(split_line[x]));
		x++;
	}
	return (EXIT_SUCCESS);
}

int	process_rows(t_map *map, int fd, t_point *src)
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
		if (!split_line || map_prepare(split_line, map, y, src) == EXIT_FAILURE)
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
int	scan_file(t_map *map, const char *file, t_point *src)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	while ((line = get_next_line(fd)))
	{
		line_count++;
		free(line);
	}
	close(fd);
	map->height = line_count;
	fd = open(file, O_RDONLY);
	if (fd < 0 || map->height == 0)
		return (EXIT_FAILURE);
	if (process_rows(map, fd, src) == EXIT_FAILURE)
	{
		ft_printf("Failed process rows\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Main entry point
int	main(int argc, char **argv)
{
	t_map	map;
	t_point	src;

	if (argc != 2)
	{
		ft_printf("Usage: %s <filename>.fdf\n", argv[0]);
		return (EXIT_FAILURE);
	}
	map.ptr_server_mlx = mlx_init();
	if (!map.ptr_server_mlx)
		return (EXIT_FAILURE);
	if (scan_file(&map, argv[1], &src) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	initialize_window(&map);
	return (EXIT_SUCCESS);
}
