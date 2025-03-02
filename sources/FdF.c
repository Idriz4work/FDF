/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:34:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/02/24 22:41:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int count_column(char **row)
{
    int column_count = 0
    while (row[column_count] != NULL)
        column_count++;
    return column_count;
}

int *asign_heigth(char **row)
{
    int i = 0
    while (row[i] != NULL)
        i++;
    i = 0;
    int *res = (int *)malloc(sizeof(int) * i);
    if (res == NULL)
    {
        perror("ERROR with asigning heigth");
        exit(EXIT_FAILURE);
        return NULL;
    }
    while (row[i] != NULL)
    {
        res[i] = row[i];
        i++;
    }
    return res;
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

// Read the map from the file
int read_map(char *filename, t_map *map,t_src *src)
{
    char **lines = NULL;
    int fd = open(filename, O_RDONLY);
        
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    lines = scan_file(fd,&src);
    if (lines == NULL)
    {
        free_array((void**)lines)
        strerror("ERROR after scaning file (read map)\n");
        exit(EXIT_FAILURE);
        return 0;
    }
    
    free_array((void **)map->grid);
    close(fd);
    return 0;
}

// TASKS
/*
The result should be displayed using an isometric projection. CHECK

Your program must display an image in a window. 

The management of the window should remain smooth (change the window, minimize it, etc.). 

Pressing the ESC key should close the window and exit the program cleanly.

Clicking on the cross at the top of the window should close the window and exit the program cleanly.


*/ 


void check_input(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char **lines;
    int fd = open(argv[1],O_RDONLY);
    lines = get_next_line(fd);
    while (lines != NULL)
    {
        if ()
        lines[i] = get_next_line(fd);
    }
    // if map is not rectangle then also quit
    
}

int grid_allocater(t_map *map)
{
    
}

void init_structs(t_dst_cds *dest_cds, t_src *three_d_cds)
{
    dest_cds->x = 0;
    dest_cds->y = 0;
    three_d_cds->x_row = 0;
    three_d_cds->y_column = 0;
    three_d_cds->z_value = 0;
}

// Main function
int main(int argc, char **argv)
{
    t_map map;
    t_dst_cds dest_cds;
    t_src three_d_cds;

    check_input(argc,argv);
    init_structs(&dest_cds,&three_d_cds);
    initialize_window(&map, argv[1]);
    return EXIT_SUCCESS;
}
