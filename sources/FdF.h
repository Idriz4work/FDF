/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:46:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/01/15 21:02:39 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/Libft/get_next_line/get_next_line.h"
# include "../includes/Libft/libft.h"
# include "../includes/ft_printf/ft_printf_bonus.h"
# include "../provided_sources/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_map
{
    void    *ptr_server_mlx;
    void    *ptr_window_mlx;
    size_t     **grid;
    size_t     rows;
    size_t     cols;
} t_map;

typedef struct s_coord
{
    float   x;
    float   y;
} t_coord;


// 30 degrees in radians
#define ISO_ANGLE 0.523599 
#define SCALE 30

// Function prototypes
int     initialize_window(t_map *maps, char *argv);
int     read_input(char *filename, t_map *maps);
void    draw_grid(t_map *maps, int **grid, int rows, int cols);
void    draw_line_dda(t_map *maps, float x1, float y1, float x2, float y2, int color);
int     key_hook(int keycode, t_map *maps);

#endif