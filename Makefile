NAME = cube_3D
CC = cc
CFLAGS = -g3 -Ofast -Ilibft -Wall -Wextra -Werror
LFLAGS = -lmlx -lXext -lX11 -lm

# main_src = main.c

files = angle.c  calculate_distance.c  directions.c  draw_func.c \
h_intersection.c  init.c  main.c  map_check.c  mlx_utils.c  parsing.c \
ray_casting.c  v_intersection.c  wall_projection.c textures.c render.c \
cleaner.c 

files_bonus = angle_bonus.c  calculate_distance_bonus.c  directions_bonus.c  draw_func_bonus.c \
h_intersection_bonus.c  init_bonus.c  main_bonus.c  map_check_bonus.c  mlx_utils_bonus.c  parsing_bonus.c \
ray_casting_bonus.c v_intersection_bonus.c  wall_projection_bonus.c minimap_bonus.c textures_bonus.c render_bonus.c \
cleaner_bonus.c map_collision_bonus.c check_images_bonus.c wall_strip_bonus.c

SRCS = $(addprefix src/, $(files))
SRCS_BONUS = $(addprefix bonus/, $(files_bonus))

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# HEADER_FILES = includes/cube.h

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(LIBFT) $(NAME)

bonus : $(LIBFT) $(OBJS) $(OBJS_BONUS) bonus/cube_bonus.h
	@rm -f $(OBJS) $(NAME)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LFLAGS) $(LIBFT) -o $(NAME)
	@echo "Bonus version compiled successfully!"

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)


$(NAME): $(OBJS) cube.h
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@echo "all cleaned successfully!"
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY : $(OBJS) $(OBJS_BONUS)