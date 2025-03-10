/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:46:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/10 16:27:10 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../includes/Libft/get_next_line/get_next_line.h"
# include "../includes/Libft/libft.h"
# include "../includes/ft_printf/ft_printf_bonus.h"
# include "../mlx_libaries/minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <sys/wait.h>

# define WIDTH 2800
# define HEIGHT 1900
# define ISO_ANGLE 0.523599 // 30 degrees in radians
# define WINDOW_TITLE "Darakci Idris WireFrame"

// Keycodes
# define ESC_KEY 65307
# define A_KEY 97
# define D_KEY 100
# define S_KEY 115
# define W_KEY 119
# define PLUS_KEY 61
# define MINUS_KEY 45
# define Z_KEY 122
# define Y_KEY 121
# define X_KEY 120
# define R_KEY 114

// Color change
# define RED 0
# define GREEN 0
# define BLUE 0

# define RIGHT -1
# define DOWN 1

// Struct Definitions
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}			t_point;

typedef struct s_channel
{
	int		red;
	int		green;
	int		blue;
}			t_rgb;

typedef struct s_dda
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;
}			t_dda;

typedef struct s_map
{
	void	*ptr_server_mlx;
	void	*ptr_window_mlx;
	t_point	**grid;
	int		width;
	int		height;
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset_x;
	int		offset_y;
	int		scale;
	int		z_scale;
}			t_map;

// Function Prototypes
int			map_prepare(char **split_line, t_map *map, int y);
int			process_rows_detailed(char **split_line, t_map *map, int y,
				char *line);
int			process_rows(t_map *map, int fd);
int			scan_file(t_map *map, const char *file);

void		free_array(void **array, int size);
void		free_splitter(void **array);
int			count_columns(char **lines);
int			count_rows(char **lines);
int			key_presser(int key, void *param);
int			close_window(void *param);
void		initialize_window(t_map *map);
t_point		**allocate_grid(int width, int height);
t_point		dimension_change(int x, int y, int z, t_map *map);
void		put_pixel_to_image(t_map *map, int x, int y, int color);
void		dda_draw_line(t_map *map, t_point start, t_point end, int color);
void		draw_wireframe(t_map *map);
void		init_image(t_map *map);
void		init_map(t_map *map);
void		redraw_window(t_map *map);

int			convert_helper(const char *input, int numeral_base);
int			ft_atoi_hex(const char *input, int base);
int			detect_base(const char *input);

void		position_mover(int key, t_map *map);
void		zoomer(int key, t_map *map);
void		scaler(int key, t_map *map);
void		put_pixel_to_image(t_map *map, int x, int y, int color);
void		clean_up(t_map *map);
void		clean_exit(t_map *map, int status);
// BONUS

// colors
// int color_shader(t_point a, t_point b,int z);
float		lerp(float start, float end, float t);
t_rgb		color_lerp(t_rgb color1, t_rgb color2, float t);
int			rgb_to_int(t_rgb color);
t_rgb		three_color_lerp(t_rgb color1, t_rgb color2, t_rgb color3, float t);
int			calculate_gradient_color(t_point p1, t_point p2, float z_value);

#endif
