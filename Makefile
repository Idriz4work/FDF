NAME = fdf

# Source files
SRCS = sources/map_parser.c sources/clean_exit.c sources/bonus_height_increase.c sources/color_increase.c sources/DDA.c sources/init.c sources/FdF.c sources/bonus_key_hooks.c  sources/dimension.c  sources/grid_spawner.c  sources/point_connecter.c sources/utils.c  sources/window_hook.c

OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc -Wall -Werror -Wextra
CFLAGS =  -g

# Include paths
INCLUDES = -I./includes/Libft -I./includes/ft_printf -I./mlx_libaries/minilibx-linux

# Libraries paths
LIBFT_DIR = includes/Libft
PRINTF_DIR = includes/ft_printf
MLX_DIR = mlx_libaries/minilibx-linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
MLX = $(MLX_DIR)/libmlx.a

# Linux-specific flags for MLX
MLX_FLAGS = -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $(OBJS) -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re