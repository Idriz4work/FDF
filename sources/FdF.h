/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:46:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/02 01:15:16 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/Libft/get_next_line/get_next_line.h"
# include "../includes/Libft/libft.h"
# include "../includes/ft_printf/ft_printf_bonus.h"
# include "../mlx_libaries/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <sys/wait.h>


typedef struct s_map
{
    void    *ptr_server_mlx;
    void    *ptr_window_mlx;
    size_t     **grid;
} t_map;

typedef struct s_data
{
    /* data */
    void *image;
} t_img;


// x = row
// y = column
// z = value of number
typedef struct s_src
{
    /* data */
    size_t xrow;
    size_t ycol;
    size_t zval;
} t_three_d;

typedef struct s_dst_cds
{
    size_t x;
    size_t y;
} t_two_d;

typedef struct s_dda
{
    float dx, dy, step;
    float x_inc, y_inc;
} t_dda;


// 30 degrees in radians
#define ISO_ANGLE 0.523599 
#define SCALE 30
// ASCII VALUES FOR MOVES
#define ESC_KEY 53  

// ERROR HANDELING

// 
int     read_map(char *filename, t_map *maps);
void    draw_grid(t_map *maps, int **grid, int rows, int cols);
void    draw_line_dda(t_map *maps,t_two_d *dest, t_three_d *src, int a);
// utils

// frees the array and sets it to null
void free_array(void **grid);


// WINDOW MANAGEMENT CLOSING HOOKING 

//
int key_presser(int key, t_map map);
//
int handle_x(t_map *map);
//
void initialize_window(t_map *map, char *filename,t_two_d *dest,t_three_d *src);

#endif