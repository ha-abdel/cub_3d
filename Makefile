NAME = cube_3D
CC = cc
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror -Ilibft
LFLAGS = -lmlx -lXext -lX11 -lm

# main_src = main.c

SRCS = main.c

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