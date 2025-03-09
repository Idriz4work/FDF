/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:17:24 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/09 23:17:38 by iatilla-         ###   ########.fr       */
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

int	process_rows_detailed(char **split_line, t_map *map, int y, char *line)
{
	int	len;

	len = 0;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	split_line = ft_split(line, ' ');
	if (!split_line || map_prepare(split_line, map, y) == EXIT_FAILURE)
	{
		free_splitter((void **)split_line);
		free(line);
		return (EXIT_FAILURE);
	}
	free_splitter((void **)split_line);
	free(line);
	return (EXIT_SUCCESS);
}

int	process_rows(t_map *map, int fd)
{
	int		y;
	char	**split_line;
	char	*line;

	y = 0;
	line = get_next_line(fd);
	split_line = NULL;
	while (line != NULL && y < map->height)
	{
		if (process_rows_detailed(split_line, map, y, line) == EXIT_FAILURE)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		y++;
		line = get_next_line(fd);
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
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	map->height = line_count;
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0 || map->height == 0)
		return (EXIT_FAILURE);
	if (process_rows(map, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
