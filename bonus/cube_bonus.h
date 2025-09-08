/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:49:21 by abdel-ha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/06 15:44:12 by abdel-ha         ###   ########.fr       */
=======
/*   Updated: 2025/09/06 15:33:50 by salahian         ###   ########.fr       */
>>>>>>> norm_1
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SCREEN_WIDTH 1500
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 64
# define FOV 60.0
# define PI 3.1415926535
# define MAP_WIDTH 26
# define MAP_HEIGHT 22
# define PLAYER_SPEED 10
# define MAX_RAY_DISTANCE 10000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define GRAY 0x808080
# define DARK_GRAY 0x404040
# define PLAYER_NORTH 0
# define PLAYER_SOUTH 1
# define PLAYER_EAST 2
# define PLAYER_WEST 3
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define O_KEY 111
# define ESC_KEY 65307

# define SAHM "wolfenstein/AnyConv.com__minimap_player-resized.xpm"

typedef enum e_wall_texture
{
	N_WALL,
	S_WALL,
	E_WALL,
	W_WALL,
	NONE
}					t_wall_texture;

typedef struct s_sprite
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
	int				frame_count;
}					t_sprite;

typedef struct s_texture
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	double			tex_step;
	double			tex_pos;
	double			wall_x;
	char			*pixel;

}					t_texture;

typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
	char			*path;
}					t_player;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_ray
{
	unsigned int	color;
	double			ray_angle;
	double			angle_step;
	double			first_y;
	double			first_x;
	double			y_step;
	double			x_step;
	double			dist_projection_plane;
	double			wall_strip;
	double			ceil;
	double			floor;
	t_point			wall_start;
	t_point			wall_end;
	t_point			ceil_start;
	t_point			ceil_end;
	t_point			floor_start;
	t_point			floor_end;
	t_point			h_intersect;
	t_point			v_intersect;
	t_point			player;
	t_point			ray_end;
	t_wall_texture	wall_type;
}					t_ray;

typedef struct s_hit
{
	int				h_hit;
	int				v_hit;
	int				is_wall;
	int				is_door;
	int				is_exit;
	int				is_h_wall;
	int				is_h_door;
	int				is_h_exit;
	int				is_v_wall;
	int				is_v_door;
	int				is_v_exit;
	int				h_door_index;
	int				v_door_index;
	int				door_index;
	double			h_dist;
	double			v_dist;
	double			distance;
}					t_hit;

typedef struct s_door
{
	int				open;
	int				col;
	int				row;
	t_sprite		frame_door;
}					t_door;

typedef struct s_exit
{
	t_sprite		frame_exit;
}					t_exit;

typedef struct s_map
{
	char			**map;
	char			*n_path;
	char			*s_path;
	char			*e_path;
	char			*w_path;
	int				direction;
	int				f_color;
	int				c_color;
	int				height;
	int				width;
}					t_map;

typedef struct minimap
{
	unsigned int	color;
	t_point			centre;
	double			r2;
}					t_minimap;

typedef struct events
{
	bool			up;
	bool			down;
	bool			left;
	bool			right;
	bool			mouse_move;
	bool			open_door;
	bool			quit;
}					t_event;

typedef struct mouse
{
	double			x;
	double			y;
	double			old_x;
}					t_mouse;

typedef struct s_data
{
	void			*mlx;
	void			*win_3d;
	void			*win_2d;
	t_door			**doors;
	int				*front_doors;
	int				nb_doors;
	int				num_rays;
	float			rotation_speed;
	int				max_dist_pixel;
	long			start_time;
	t_event			event;
	t_mouse			mouse;
	t_player		player;
	t_sprite		bg;
	t_sprite		bg1;
	t_sprite		n_wall;
	t_sprite		s_wall;
	t_sprite		e_wall;
	t_sprite		w_wall;
	t_sprite		minimap;
	t_sprite		door;
	t_sprite		exit_sprite;
	t_exit			exit;
	t_minimap		mini_map;
	t_map			map;
	t_hit			hit;
}					t_data;
void				print_data(t_data *data);
void				print_info(t_data *data);
void				print_hit_info(t_data *data);
int					check_if_open(t_data **data, int index, int horizontal,
						t_ray *ray);
int					get_door_index(t_data *data, t_point p);
t_point				construct_point(int x, int y);
void				print_map(char **map);
int					main_function_parsing(t_data *data, char *file);
int					map_check(t_data *data, char *file, char *line, int fd);
void				get_imgs_addresses(t_data **data);
void				init_data(t_data *data);
void				get_texture_img(t_data *data, t_ray **ray, t_sprite *img);
void				copy_img(t_sprite *src, t_sprite **dst);
void				set_wall_type(t_ray **ray, t_data *data);
int					destroy_window(t_data *data);
int					clean_all(t_data **data);
void				clean_mlx_mandatory_resources(t_data **data);
int					render(t_data *data);
int					get_t(int trgb);
int					is_door(t_data *data, double x, double y);
void				wall_projection(t_data *data, t_ray *ray, int col);
void				check_vertical_intersect(t_data *data, t_ray *ray);
void				calc_vertical_step(t_data *data, t_ray *ray,
						double tan_val);
void				calc_first_v_intersect(t_data *data, t_ray *ray,
						double tan_val);
void				init_ray(t_ray *ray, t_data *data);
void				check_horizontal_intersect(t_data *data, t_ray *ray);
void				calc_horizontal_step(t_data *data, t_ray *ray,
						double tan_val);
void				calc_first_h_intersect(t_data *data, t_ray *ray,
						double tan_val);
void				calc_distance(t_data *data, t_ray *ray);
void				normalize_angle(double *angle);
int					is_perpendicular_to_xaxis(double ray_angle);
int					is_perpendicular_to_yaxis(double ray_angle);
int					is_facing_right(double angle);
int					is_facing_left(double angle);
int					is_facing_down(double angle);
int					is_facing_up(double angle);
int					is_wall(t_data *data, double x, double y);
void				my_mlx_pixel_put(t_sprite *img, int x, int y, int color);
int					inside_bounds(t_data *data, double x, double y);
void				draw_square(t_data *data, int x, int y, int color);
void				draw_line(t_data *data, t_point start_p, t_point end_p,
						int color);
void				draw_walls(t_data *data);
void				draw_grid_lines(t_data *data);
void				draw_player(t_data *data);
void				draw_direction_lines(t_data *data);
void				init_data(t_data *data);
void				initial_data(t_data *data);
void				cast_rays(t_data *data);
void				draw_map(t_data *data);
void				clear_image(t_sprite *img, int color);
void				create_minimap(t_data *data);
unsigned int		get_color(t_sprite *img, int x, int y);
void				animate_door(t_data *data);
void				fill_img_door(t_data *data);

<<<<<<< HEAD
void				init_wall_images(t_data **data);
void				check_walls_addresses(t_data **data);
void				check_addresses(t_data **data);
int					release_key(int key, t_data *data);
long				get_time(void);
void				init_images(t_data **data);
void				calc_vertical_step(t_data *data, t_ray *ray,
						double tan_val);
void				calc_first_v_intersect(t_data *data, t_ray *ray,
						double tan_val);
void				calc_horizontal_step(t_data *data, t_ray *ray,
						double tan_val);
void				calc_first_h_intersect(t_data *data, t_ray *ray,
						double tan_val);
double				handle_division_by_zero(double angle);
int					check_if_open(t_data **data, int index, int horizontal,
						t_ray *ray);
int					is_exit(t_data *data, double x, double y);
int					get_door_index(t_data *data, t_point p);
int					check_distance(t_data *data);
void				get_the_closest_door(t_data *data);
void				fill_img_door(t_data *data);
int					handle_mouse(int x, int y, t_data *data);
void				get_the_closest_door(t_data *data);
int					handle_key(int key, t_data *data);
void				check_collision(t_data *data, double old_px, double old_py);
void				move_player(t_data *data);
void				print_info(t_data *data);
void				print_hit_info(t_data *data);
long				get_time(void);
=======
/* FUNCTIONS */
int	release_key(int key, t_data *data);
void	set_direction(t_data *data, int key);
long	get_time(void);
int	is_facing_right1(double angle);
int	is_facing_left1(double angle);
int	is_facing_down1(double angle);
int	is_facing_up1(double angle);
void	init_images(t_data **data);
void	calc_vertical_step(t_data *data, t_ray *ray, double tan_val);
void	calc_first_v_intersect(t_data *data, t_ray *ray, double tan_val);
void	calc_horizontal_step(t_data *data, t_ray *ray, double tan_val);
void	calc_first_h_intersect(t_data *data, t_ray *ray, double tan_val);
double	handle_division_by_zero(double angle);
int	check_if_open(t_data **data, int index, int horizontal, t_ray *ray);
int	is_exit(t_data *data, double x, double y);
int	get_door_index(t_data *data, t_point p);
int	check_distance(t_data *data);
void	get_the_closest_door(t_data *data);
void	fill_img_door(t_data *data);
int	handle_mouse(int x, int y, t_data *data);
void	get_the_closest_door(t_data *data);
int	handle_key(int key, t_data *data);
void	check_collision(t_data *data, double old_px, double old_py);
void	move_player(t_data *data);
void	print_front_doors(t_data *data);
void	print_info(t_data *data);
void	print_hit_info(t_data *data);
void	animate_door(t_data *data);
void	animate_exit(t_data *data);
int	calculate_lines(char *buf);
int	check_every_character(char *s);
char	*get_new_line(char *str, int size);
int	get_long_line(char **map);
int	fill_map(char **map, char *line, int fd);
int		get_last_slash(char *file);
int		check_data(t_data *data);
int		check_is_map(char *line);
int		fill_data(t_data *data, char *line, char *s, int index);
void		take_path(t_data *data, char *line, char *s, int index);
int		help_fill_data(t_data *data, char *tmp, char *s, int *count);
char *append_char(char c);
void	fill_tmp(char **tmp);
int		parse_spaces(char *line, int *index, int flag);
int		check_is_valid_param(char **tmp, char *str, char **s);
int	handle_direction(t_data *data, char c, int i, int j);
int	fill_color(t_data *data, char *s, char *tmp, int count);
int		take_color(t_data *data, char *line, char *s, int index);
void	rotate_the_map(t_data *data, t_point wxy, t_point dxy);
>>>>>>> norm_1

#endif