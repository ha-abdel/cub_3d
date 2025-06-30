#ifndef CUBE_H
# define CUBE_H

#define TILE_SIZE 100
#define FOV 60.0
#define NUM_RAYS 1600
#define PI 3.1415926535
#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define PLAYER_SPEED 5
#define ROTATION_SPEED 0.1
#define MAX_RAY_DISTANCE 10000
#define MAX_DIST_PIXEL 3200


// Color definitions
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define GRAY 0x808080
#define DARK_GRAY 0x404040

#define PLAYER_NORTH 0
#define PLAYER_SOUTH 1
#define PLAYER_EAST 2
#define PLAYER_WEST 3

#define RIGHT_ARROW 65363
#define LEFT_ARROW 65361
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define ESC_KEY 65307

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_sprite
{
	void				*img;
	int					width;
	int					height;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	// int					frame_count;
	// int					frame_index;
	// char				action;
	// int					dir;
}						t_sprite;

// typedef struct s_validation_infos
// {
// 	int					count_player;
// 	int					count_coin;
// 	int					count_exit;
// 	int					count_enemy;
// 	int					ex;
// 	int					ey;
// 	int					px;
// 	int					py;
// 	int					width;
// 	int					height;
// 	int					collide;
// }						t_validation_infos;

typedef struct s_player {
    double x;
    double y;
    double angle;
	char *path;
    int is_facing_up;
    int is_facing_down;
    int is_facing_right;
    int is_facing_left;
} t_player;


typedef struct s_map
{
	char	**map;
	int		direction;
	int		f_color;
	int		c_color;
	int		height;
	int		width;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
}	t_map;

typedef struct s_data
{
	void				*mlx;
	// void				*win;
	void 				*win_3d;
    void 				*win_2d;
    t_player 			player;
	t_sprite 			bg;
	t_sprite 			bg1;
	t_player			player;
	t_map				map;
}						t_data;
void	print_map(char **map);
int		main_function_parsing(t_data *data, char *file);
int		map_check(t_data *data, char *file, char *line, int fd);

#endif