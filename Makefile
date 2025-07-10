NAME = cube_3D
CC = cc
CFLAGS = -g3 -Ofast -fsanitize=address -Ilibft -Wall -Wextra -Werror -Ilibft
LFLAGS = -lmlx -lXext -lX11 -lm

# main_src = main.c

files = angle.c  calculate_distance.c  directions.c  draw_func.c \
h_intersection.c  init.c  main.c  map_check.c  mlx_utils.c  parsing.c \
ray_casting.c  v_intersection.c  wall_projection.c

SRCS = $(addprefix src/, $(files))

OBJS = $(SRCS:.c=.o)

HEADER_FILES = includes/cube.h

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	@$(CC) $(SRCS) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re