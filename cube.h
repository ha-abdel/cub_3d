#ifndef CUBE_H
# define CUBE_H

//# define ESCAPE 65307
//# define LEFT 97
//# define UP 119
//# define RIGHT 100
//# define DOWN 115

//# define TILE_SIZE 64

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

// typedef struct s_sprite
// {
// 	void				*img;
// 	int					width;
// 	int					height;
// 	char				*addr;
// 	int					bpp;
// 	int					line_len;
// 	int					endian;
// 	int					frame_count;
// 	int					frame_index;
// 	char				action;
// 	int					dir;
// }						t_sprite;

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
	double	x;
	double	y;
	double	angle;
}	t_player;


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
	void				*win;
	t_player			player;
	t_map				map;
}						t_data;
void	print_map(char **map);
int		main_function_parsing(t_data *data, char *file);
int		map_check(t_data *data, char *file, char *line, int fd);

#endif