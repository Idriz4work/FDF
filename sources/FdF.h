/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:46:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/04 00:18:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/Libft/get_next_line/get_next_line.h"
# include "../includes/Libft/libft.h"
# include "../includes/ft_printf/ft_printf_bonus.h"
# include "../mlx_libaries/minilibx-linux/mlx.h"
// # include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_map
{
	void	*ptr_server_mlx;
	void	*ptr_window_mlx;
	size_t	**grid;
}			t_map;

typedef struct s_data
{
	/* data */
	void	*image;
	size_t	x;
	size_t	y;
}			t_img;

// x = row
// y = column
// z = value of number
typedef struct s_src
{
	/* data */
	size_t	x_row;
	size_t	y_column;
	size_t	z_value;
}			t_src;

// 30 degrees in radians
# define ISO_ANGLE 0.523599
# define SCALE 30

// ASCII VALUES FOR MOVES
# define ESC_KEY 53
// left
# define A_KEY 65
// right
# define D_KEY 68
// down
# define S_KEY 83
// up
# define W_KEY 87

// ERROR HANDELING

// DDA ALgorithm / connecting points and also changing dimension
void		pixel_draw(t_map *map, t_img *img_coords);
void		draw_line_dda(t_map *map, t_img *start, t_src *end);
void		dimension_changer(t_src *three_d, t_img *two_d, int angle);

// utils

// frees the array and sets it to null
void		free_array(void **grid);

// WINDOW MANAGEMENT CLOSING HOOKING

//
int			key_presser(int key, t_map *map);
//
int			handle_x(t_map *map);
//
void		initialize_window(t_map *map, t_img *dest, t_src *src);

// BONUS MOVER
void		move_position_left(void);
void		move_position_right(void);
void		move_position_up(void);
void	move_position_down(;)

#endif