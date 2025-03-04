/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/04 03:35:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

//
void	pixel_draw(t_map *map, t_img *img_coords)
{
    img_coords->image = mlx_pixel_put(map->ptr_server_mlx, map->ptr_window_mlx,
            img_coords.x, img_coords.y, 0x00FF00);
}

//
size_t	**grid_allocater(size_t width, size_t heigth)
{
    size_t **grid;
    
    return (grid);
}

//
int	count_column(char **row)
{
	int	column_count;

	column_count = 0;
	while (row[column_count] != NULL)
		column_count++;
	return (column_count);
}

//
void	initialize_ground(t_src *src_points, t_map *map)
{
	size_t	width;
	size_t	height;

	width = src_points.y;
	height = src_points.x;
    map->grid = grid_allocater()
}

//
int	scan_file_helper(t_src *src_points, t_img *img_coords, t_map *map, int file,
		char **lines)
{
	size_t	i;
	size_t	column_size;

	i = 0;
	column_size = 0;
	while (lines != NULL)
	{
		lines = get_next_line(file);
		if (lines == NULL)
		{
			perror("ERROR with allocating size for lines\n");
			free_array(lines);
			return (EXIT_FAILURE);
		}
		src_points->x_row++;
		src_points->y_column = count_column(ft_split(lines, ' '));
		if (i > 0 && src_points->y_column != column_size)
		{
			ft_printf("The column size is not constant: \n[prev: %zu\tcurrent:
				%zu]\n", column_size, src_points->y_column);
			free_array(lines);
			return (EXIT_FAILURE);
		}
		column_size = src_points->y_column;
		dimension_changer(src_points, img_coords, ISO_ANGLE);
		pixel_draw(map, img_coords);
		i++;
	}
	return (0);
}

// read the inside of the file and then changed dimensions
// after the dimensions are change we start to put each coordinate
// into its right place so we prepare the wireframe points
int	scan_file(t_src *src_points, t_img *img_coords, t_map *map, int file)
{
	char	*lines;

	lines = get_next_line(file);
	if (lines == '\0' || lines == NULL)
	{
		ft_printf("empty map [scanfile]\n");
		free_array(&lines);
		return (EXIT_FAILURE);
	}
	scan_file_helper(src_points, img_coords, map, file, lines);
	img_coords->image = mlx_new_image(map->ptr_server_mlx, 400, 400);
	return (EXIT_SUCCESS);
}







// 1. Read from the file & error handle empty files
// 2. call scan_file which will read the file & put pixels into right place
// 3. draw ground for image
// 4. draw the image & connect the prepared pixels from scan_file
int	wireframe_starter(int file, t_src *src_points, t_img *img_coords,
		t_map *map)
{
	if (scan_file(src_points, img_coords, file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	initialize_ground(src_points->y_column, src_points->x_row);
	write_to_image(src_points);
	return (EXIT_SUCCESS);
}




// checks the provided input from the user
// and makes sure that only valid arguments are entered
int	check_input(int argc, char **argv)
{
	size_t	len;

	len = 0;
	if (argc != 2)
	{
		ft_printf("Usage: %s <filename>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len - 1] != 'f' || argv[1][len - 2] != 'd'
		|| argv[1][len - 3] != 'f' || argv[1][len - 4] != '.')
	{
		ft_printf("%s <filename>.fdf (needs type of: .fdf)\n", argv[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// 1. read input and handle acordingly
// 2. initialize structs and then initialize a window
// 3. continue scanning the inside of the provided file
int	main(int argc, char **argv)
{
	t_map	map;
	t_img	img_coords;
	t_src	src_coords;
	int		fd;

	if (check_input(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR opening file");
		return (EXIT_FAILURE);
	}
	init_structs(&img_coords, &src_coords);
	initialize_window(&map, &img_coords, &src_coords);
	if (wireframe_starter(fd, &src_coords, &img_coords, &map) == EXIT_FAILURE)
	{
		free_array(map.grid);
		free_array((void *)&img_coords.image);
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

// int	main(void)
// {
//     void	*mlx; //display
//     void	*mlx_win; //window
//     t_img	image; //image
//     mlx = mlx_init(); //display init
//     mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!"); //window init
//     image.image = mlx_new_image(mlx, 1920, 1080); //image init
// }