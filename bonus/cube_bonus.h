#ifndef CUBE_H
# define CUBE_H

#define screen_width 1500
#define screen_height 1000
#define TILE_SIZE 64
#define FOV 60.0
// #define NUM_RAYS 3000
#define PI 3.1415926535
#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define PLAYER_SPEED 5
#define ROTATION_SPEED M_PI / 300
#define MAX_RAY_DISTANCE 10000
#define MAX_DIST_PIXEL screen_width * 2


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

typedef enum e_wall_texture
{
    N_WALL, S_WALL, E_WALL, W_WALL, NONE
} t_wall_texture;

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
}						t_sprite;


typedef struct s_player {
    double x;
    double y;
    double angle;
	char *path;
} t_player;

typedef struct s_point
{
	double x;
	double y;
} t_point;

typedef struct s_ray
{
	unsigned int color;
	double	ray_angle;
	double	angle_step;
	double	distance;
	double	first_y;
	double	first_x;
	double	y_step;
	double	x_step;
	double	h_dist;
	double	v_dist;
	double	dist_projection_plane;
	double	wall_strip;
	double	ceil;
	double	floor;
	t_point	wall_start;
	t_point	wall_end;
	t_point	ceil_start;
	t_point	ceil_end;
	t_point	floor_start;
	t_point	floor_end;
	t_point h_intersect;
	t_point	v_intersect;
	t_point	player;
	t_point ray_end;
	t_wall_texture	wall_type;
} t_ray;

typedef struct s_map
{
	char	**map;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	int		direction;
	int		f_color;
	int		c_color;
	int		height;
	int		width;
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
	t_sprite 			N_wall;
	t_sprite 			S_wall;
	t_sprite 			E_wall;
	t_sprite 			W_wall;
	t_map				map;
	int					NUM_RAYS;
}						t_data;
void	print_map(char **map);
int		main_function_parsing(t_data *data, char *file);
int		map_check(t_data *data, char *file, char *line, int fd);


/* FUNCTIONS */
void    wall_projection(t_data *data, t_ray *ray, int *color, int col);
void check_vertical_intersect(t_data *data, t_ray *ray);
void    calc_vertical_step(t_data *data, t_ray *ray, double tan_val);
void    calc_first_v_intersect(t_data *data, t_ray *ray, double tan_val);
void    init_ray(t_ray *ray, t_data *data);
void check_horizontal_intersect(t_data *data, t_ray *ray);
void    calc_horizontal_step(t_data *data, t_ray *ray, double tan_val);
void    calc_first_h_intersect(t_data *data, t_ray *ray, double tan_val);
void    calc_distance(t_data *data, t_ray *ray, int *color);
void    normalize_angle(double *angle);
int is_perpendicular_to_Xaxis(double ray_angle);
int is_perpendicular_to_Yaxis(double ray_angle);
int is_facing_right(double angle);
int is_facing_left(double angle);
int is_facing_down(double angle);
int is_facing_up(double angle);
void ft_player_debug(t_data * data);
int is_wall(t_data *data, double x, double y);
int    render(t_data *data);
void	my_mlx_pixel_put(t_sprite *img, int x, int y, int color);
int inside_bounds(t_data *data, double x, double y) ;
void draw_square(t_data *data, int x, int y, int color, int win);
void draw_line(t_data *data, t_point start_p, t_point end_p, int color, int win);
void    draw_walls(t_data *data);
void    draw_grid_lines(t_data *data);
void    draw_player(t_data *data);
void    draw_direction_lines(t_data *data);
void    init_data(t_data *data);
void    initial_data(t_data *data);
void cast_rays(t_data *data);
void draw_map(t_data *data) ;
void clear_image(t_sprite *img, int color);

#endif