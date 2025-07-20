#include "cube_bonus.h"

void	draw_wall_texture(t_data *data, t_ray *ray)
{
	t_sprite	img;
	t_texture	texture;
	int			y;

	y = ray->wall_start.y;
	get_texture_img(data, ray, &img);
	if (ray->h_dist < ray->v_dist)
		texture.wall_x = fmod(ray->ray_end.x, TILE_SIZE) / TILE_SIZE;
	else
		texture.wall_x = fmod(ray->ray_end.y, TILE_SIZE) / TILE_SIZE;
	texture.tex_x = (int)(texture.wall_x * (img.width - 1));
	texture.tex_step = img.height / ray->wall_strip;
	texture.tex_pos = (ray->wall_start.y - SCREEN_HEIGHT / 2 + ray->wall_strip
			/ 2) * texture.tex_step;
	while (y < ray->wall_end.y)
	{
		texture.tex_y = (int)texture.tex_pos % img.height;
		texture.pixel = img.addr + (texture.tex_y * img.line_len)
			+ (texture.tex_x * (img.bpp / 8));
		texture.color = *(unsigned int *)texture.pixel;
		texture.tex_x = texture.tex_x % img.width;
		texture.tex_y = texture.tex_y % img.height;
		my_mlx_pixel_put(&data->bg1, ray->wall_start.x, y++, texture.color);
		texture.tex_pos += texture.tex_step;
	}
}

void	animate_door(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < 250)
	{
		x = data->frame_door.frame_count;
		while (x < (data->frame_door.frame_count + 250))
		{
			color = get_color(&data->door, x, y);
			if (color != 0x00000000)
				my_mlx_pixel_put(&data->frame_door, x
					- data->frame_door.frame_count, y, color);
			x++;
		}
		y++;
	}
	if (data->frame_door.frame_count < 1000)
		data->frame_door.frame_count += 250;
	else
		data->frame_door.frame_count = 0;
}

void	draw_door_texture(t_data *data, t_door *door, t_ray *ray)
{
	t_texture		texture;
	int				y;
	unsigned int	color;

	(void)ray;
	y = door->ray.wall_start.y;
	if (door->ray.h_dist < door->ray.v_dist)
		texture.wall_x = fmod(door->ray.h_intersect.x, TILE_SIZE) / TILE_SIZE;
	else
		texture.wall_x = fmod(door->ray.v_intersect.y, TILE_SIZE) / TILE_SIZE;
	texture.tex_x = (int)(texture.wall_x * (data->frame_door.width - 1));
	texture.tex_step = data->frame_door.height / door->ray.wall_strip;
	texture.tex_pos = (door->ray.wall_start.y - SCREEN_HEIGHT / 2
			+ door->ray.wall_strip / 2) * texture.tex_step;
	while (y < door->ray.wall_end.y)
	{
		texture.tex_y = (int)texture.tex_pos % data->frame_door.height;
		color = get_color(&data->frame_door, texture.tex_x, texture.tex_y);
		if (get_t(color) != 0xFF)
			my_mlx_pixel_put(&data->bg1, door->ray.wall_start.x, y, color);
		texture.tex_pos += texture.tex_step;
		y++;
	}
}

void	project_wall(t_ray **ray, int col)
{
	(*ray)->dist_projection_plane = (SCREEN_WIDTH / 2.0) / tan((FOV / 2.0) * PI
			/ 180);
	(*ray)->wall_strip = (TILE_SIZE / (*ray)->distance)
		* (*ray)->dist_projection_plane;
	(*ray)->ceil = (SCREEN_HEIGHT) / 2 - (*ray)->wall_strip / 2;
	(*ray)->floor = (*ray)->ceil + (*ray)->wall_strip;
	if ((*ray)->ceil < 0)
		(*ray)->ceil = 0;
	if ((*ray)->floor > SCREEN_HEIGHT)
		(*ray)->floor = SCREEN_HEIGHT;
	(*ray)->wall_start.x = col;
	(*ray)->wall_start.y = (*ray)->ceil;
	(*ray)->wall_end.x = col;
	(*ray)->wall_end.y = (*ray)->floor;
	(*ray)->ceil_start.x = col;
	(*ray)->ceil_start.y = 0;
	(*ray)->ceil_end.x = col;
	(*ray)->ceil_end.y = (*ray)->ceil - 1;
	(*ray)->floor_start.x = col;
	(*ray)->floor_start.y = (*ray)->ceil + (*ray)->wall_strip;
	(*ray)->floor_end.x = col;
	(*ray)->floor_end.y = SCREEN_HEIGHT;
}

void	project_door(t_door **door, int col)
{
	(*door)->ray.dist_projection_plane = (SCREEN_WIDTH / 2.0) / tan((FOV / 2.0)
			* PI / 180);
	(*door)->ray.wall_strip = (TILE_SIZE / (*door)->ray.distance)
		* (*door)->ray.dist_projection_plane;
	(*door)->ray.ceil = (SCREEN_HEIGHT) / 2 - (*door)->ray.wall_strip / 2;
	(*door)->ray.floor = (*door)->ray.ceil + (*door)->ray.wall_strip;
	if ((*door)->ray.ceil < 0)
		(*door)->ray.ceil = 0;
	if ((*door)->ray.floor > SCREEN_HEIGHT)
		(*door)->ray.floor = SCREEN_HEIGHT;
	(*door)->ray.wall_start.x = col;
	(*door)->ray.wall_start.y = (*door)->ray.ceil;
	(*door)->ray.wall_end.x = col;
	(*door)->ray.wall_end.y = (*door)->ray.floor;
	(*door)->ray.ceil_start.x = col;
	(*door)->ray.ceil_start.y = 0;
	(*door)->ray.ceil_end.x = col;
	(*door)->ray.ceil_end.y = (*door)->ray.ceil - 1;
	(*door)->ray.floor_start.x = col;
	(*door)->ray.floor_start.y = (*door)->ray.ceil + (*door)->ray.wall_strip;
	(*door)->ray.floor_end.x = col;
	(*door)->ray.floor_end.y = SCREEN_HEIGHT;
}

void	draw_wall_behind_door(t_data *data, int col, t_ray **ray, t_door **door)
{
	(*door)->ray.ray_angle = (*ray)->ray_angle;
	project_door(&door, col);
	if ((*door)->ray.distance >= (*ray)->distance)
	{
		draw_wall_texture(data, ray);
		draw_line(data, (*ray)->ceil_start, (*ray)->ceil_end, data->map.c_color,
			1);
		draw_line(data, (*ray)->floor_start, (*ray)->floor_end,
			data->map.f_color, 1);
	}
	else
	{
		draw_line(data, (*door)->ray.ceil_start, (*door)->ray.ceil_end,
			data->map.c_color, 1);
		draw_line(data, (*door)->ray.floor_start, (*door)->ray.floor_end,
			data->map.f_color, 1);
		draw_wall_texture(data, ray);
		draw_door_texture(data, door, ray);
	}
}

void	wall_projection(t_data *data, t_ray *ray, int col, t_door *door)
{
	project_wall(&ray, col);
	if (door->found_door)
	{
		draw_wall_behind_door(data, col, &ray, &door);
	}
	else
	{
		draw_wall_texture(data, ray);
		draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
		draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
	}
}
