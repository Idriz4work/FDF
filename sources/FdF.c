/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/06 01:06:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

// counts the number of spaces in the current column
// it then checks if that number is the same as the number before
static int column_check(char *lines, int column_size)
{
    int prev_size = 0;
    int i = 0;
    while (lines[i] != '\n' && lines[i] != '\0') // Fixed condition (|| → &&)
    {
        prev_size++;
        i++;
    }
    if (column_size != prev_size)
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS; // Fixed typo EXIT_SUCCES → EXIT_SUCCESS
}

// return the number of columns
int count_columns(char **lines)
{
    int column = 0;
    int size_column = 0;
    while (lines[column] != NULL)
    {
        while (lines[column][size_column] != '\n' && lines[column][size_column] != '\0')
            size_column++;
        if (column_check(lines[column], size_column) == EXIT_FAILURE)
        {
            ft_printf("File has an inconsistent column value");
            return EXIT_FAILURE;
        }
        column++; // Missing increment to avoid infinite loop
    }
    return column;
}

// returns number of rows
int count_rows(char **lines)
{
    int rows = 0;
    while (lines[rows] != NULL)
        rows++;
    return rows;
}

// this function makes sure that we draw the pixel on the right coordinates
// so that we will get an isometric object later when we connect
// the points and they turn out to be lines
void image_populator(t_map *map, t_point src_points, t_img *image)
{
    // Function implementation needed
}

// First pass: determine width
// Populate grid
int map_prepare(char **split_line, t_map *map, int x, int y, t_img *image)
{
    if (y == 0)
    {
        map->width = count_columns(split_line);
        map->height = count_rows(split_line);
        map->grid = allocate_grid(map->width, map->height);
    }
    while (split_line[x] != NULL)
    {
        map->grid[y][x].x = x;
        map->grid[y][x].y = y;
        map->grid[y][x].z = ft_atoi(split_line[x]);
        dimension_change(&map->grid[y][x], 20, image);
        x++;
    }
    return x;
}

// read the inside of the file and then change dimensions
// after the dimensions are changed, we start to put each coordinate
// into its right place, so we prepare the wireframe points
int scan_file(t_point *src_points, t_img *img_coords, t_map *map, const char *file) // Changed file type to `const char *`
{
    int fd;
    char *line;
    char **split_line;
    int y = 0;
    int x = 0;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return EXIT_FAILURE;
    while ((line = get_next_line(fd)) != NULL)
    {
        split_line = ft_split(line, ' ');
        x = map_prepare(split_line, map, x, y, img_coords);
        image_populator(map, *src_points, img_coords); // Added missing argument
        free_array((void *)split_line);
        free(line);
        y++;
    }
    map->height = y;
    close(fd);
    return EXIT_SUCCESS;
}

// 1. Read from the file & handle errors for empty files
// 2. Call scan_file which will read the file & put pixels into the right place
// 3. Draw ground for image
// 4. Draw the image & connect the prepared pixels from scan_file
int wireframe_starter(const char *file, t_point *src_points, t_img *img_coords, t_map *map) // Changed file type
{
    img_coords->image = mlx_new_image(map->ptr_server_mlx, 400, 400);
    img_coords->addr = mlx_get_data_addr(img_coords->image,
                                         &img_coords->bits_per_pixel, // Fixed incorrect pointer conversion
                                         &img_coords->line_length, 
                                         &img_coords->endian);
    if (scan_file(src_points, img_coords, map, file) == EXIT_FAILURE)
        return EXIT_FAILURE;
    // draw_image_lines(map, img_coords); // Ensure function prototype is present
    
    // seg fault 
    mlx_put_image_to_window(map->ptr_server_mlx, map->ptr_window_mlx,
                            img_coords->image, 0, 0);
    return EXIT_SUCCESS;
}

// checks the provided input from the user
// and makes sure that only valid arguments are entered
int check_input(int argc, char **argv)
{
    size_t len;

    if (argc != 2)
    {
        ft_printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    len = ft_strlen(argv[1]);
    if (len < 4 || ft_strncmp(argv[1] + len - 4, ".fdf",len) != 0)
    {
        ft_printf("%s <filename>.fdf (needs type: .fdf)\n", argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// 1. Read input and handle accordingly
// 2. Initialize structs and then initialize a window
// 3. Continue scanning the inside of the provided file
int main(int argc, char **argv)
{
    t_map map;
    t_img img_coords;
    t_point src_coords;
    int fd;

    if (check_input(argc, argv) == EXIT_FAILURE)
        return EXIT_FAILURE;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("ERROR opening file");
        return EXIT_FAILURE;
    }
    init_structs(&img_coords, &src_coords);
    map.ptr_server_mlx = mlx_init();
	if (!map.ptr_server_mlx)
	{
		perror("Failed to set up server");
		exit(EXIT_FAILURE);
	}
    if (wireframe_starter(argv[1], &src_coords, &img_coords, &map) == EXIT_FAILURE)
    {
        free_array((void *)map.grid);
        free_array((void *)&img_coords.image);
        close(fd);
        return EXIT_FAILURE;
    }
    initialize_window(&map, &img_coords, &src_coords);
    close(fd);
    return EXIT_SUCCESS;
}
