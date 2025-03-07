/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:46:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/03/07 01:59:19 by marvin           ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 800
# define ISO_ANGLE 0.523599 // 30 degrees in radians
# define WINDOW_TITLE "Darakci Idris WireFrame"

// Keycodes
# define ESC_KEY 53
# define A_KEY 65
# define D_KEY 68
# define S_KEY 83
# define W_KEY 87

// Struct Definitions
typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}			t_point;

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
}			t_map;

// Function Prototypes
void		free_array(void **array);
void		init_structs(t_map *map);
int			create_trgb(int t, int r, int g, int b);
int			count_columns(char **lines);
int			count_rows(char **lines);
int			key_presser(int key, t_map *map);
int			close_window(t_map *map);
void		initialize_window(t_map *map);
t_point		**allocate_grid(int width, int height);
void		put_pixel_to_image(t_map *map, int x, int y, int color);
t_point		dimension_change(int x, int y, int z, t_map *map);
void		draw_line(t_map *map, t_point start, t_point end, int color);
void		draw_wireframe(t_map *map);
void		init_image(t_map *map);

#endif
