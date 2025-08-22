/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:49:21 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/22 16:20:53 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SCREEN_WIDTH 1500
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 64
# define FOV 60.0
# define PI 3.1415926535
# define MAP_WIDTH 26
# define MAP_HEIGHT 22
# define PLAYER_SPEED 5
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
	// double			distance;
	double			first_y;
	double			first_x;
	double			y_step;
	double			x_step;
	// double			h_dist;
	// double			v_dist;
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
	int				is_h_wall;
	int				is_v_wall;
	int				is_h_door;
	int				is_v_door;
	int				h_door_index;
	int				v_door_index;
	int				door_index;
	double			h_dist;
	double			v_dist;
	double			distance;
	
} t_hit;

typedef struct s_door
{
	// int				found_door;
	// int				found_door_pixel;
	// int				wall_behind_distance;
	int				open;
	int				col;
	int				row;
	t_sprite		frame_door;
	// t_sprite		sprite_door;
	t_ray			ray;

}					t_door;

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



typedef struct s_data
{
	void			*mlx;
	void			*win_3d;
	void			*win_2d;
	t_player		player;
	t_sprite		bg;
	t_sprite		bg1;
	t_sprite		n_wall;
	t_sprite		s_wall;
	t_sprite		e_wall;
	t_sprite		w_wall;
	t_sprite		minimap;
	t_minimap		mini_map;
	t_map			map;
	t_door			**doors;
	t_sprite		door;
	// t_sprite		frame_door;
	t_hit			hit;
	int				num_rays;
	float			rotation_speed;
	int				max_dist_pixel;
}					t_data;

void	print_hit_info(t_data *data);
int	check_if_open(t_data **data, int index, int horizontal, t_ray *ray);
int	get_door_index(t_data *data, t_point p);
t_point	construct_point(int	x, int y);
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
void				calc_wall_ditance(t_data *data, t_ray **ray, t_door **door);
void				calc_door_ditance(t_data *data, t_ray **ray, t_door **door);
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
void				ft_player_debug(t_data *data);
int					is_wall(t_data *data, double x, double y);
// int					render(t_data *data);
void				my_mlx_pixel_put(t_sprite *img, int x, int y, int color);
int					inside_bounds(t_data *data, double x, double y);
void				draw_square(t_data *data, int x, int y, int color, int win);
void				draw_line(t_data *data, t_point start_p, t_point end_p,
						int color, int win);
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
void	fill_img_door(t_data *data);
#endif