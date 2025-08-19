/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:27:24 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/24 15:37:13 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


int check_zone(t_data *data, t_door *door)
{
    double door_cx = door->x * TILE_SIZE + TILE_SIZE / 2;
    double door_cy = door->y * TILE_SIZE + TILE_SIZE / 2;

    double dx = door_cx - data->player.x;
    double dy = door_cy - data->player.y;

    double angle_to_door = atan2(dy, dx);

    double diff = angle_to_door - data->player.angle;

    if (diff > M_PI)
        diff -= 2 * M_PI;
    else if (diff < -M_PI)
        diff += 2 * M_PI;

    return (fabs(diff) <= FOV / 2);
}

// int get_the_closest_door(t_data *data)
// {
//     int     i;
//     int     index = -1;
//     int     dt = INT_MAX;

//     i = 0;
//     while (data->door[i])
//     {
//         int dx = abs(data->door[i]->x - (int)(data->player.x / TILE_SIZE));
//         int dy = abs(data->door[i]->y - (int)(data->player.y / TILE_SIZE));
//         int dist = dx + dy;

//         if (dist < dt && check_zone(data, data->door[i]))
//         {
//             dt = dist;
//             index = i;
//         }
//         i++;
//     }
//     return (index);
// }

void	draw_wall_texture(t_data *data, t_ray **ray)
{
	t_sprite	img;
	t_texture	texture;
	int			y;

	y = (*ray)->wall_start.y;
	get_texture_img(data, ray, &img);
	if ((*ray)->h_dist < (*ray)->v_dist)
		texture.wall_x = fmod((*ray)->ray_end.x, TILE_SIZE) / TILE_SIZE;
	else
		texture.wall_x = fmod((*ray)->ray_end.y, TILE_SIZE) / TILE_SIZE;
	texture.tex_x = (int)(texture.wall_x * (img.width - 1));
	texture.tex_step = img.height / (*ray)->wall_strip;
	texture.tex_pos = ((*ray)->wall_start.y - screen_height / 2
			+ (*ray)->wall_strip / 2) * texture.tex_step;
	// printf("y=[%d]/////////////wall_end=[%.2f]\n", y, (*ray)->wall_end.y);
	while (y < (*ray)->wall_end.y)
	{
		texture.tex_y = (int)texture.tex_pos % img.height;
		texture.pixel = img.addr + (texture.tex_y * img.line_len)
			+ (texture.tex_x * (img.bpp / 8));
		texture.color = *(unsigned int *)texture.pixel;
		texture.tex_x = texture.tex_x % img.width;
		texture.tex_y = texture.tex_y % img.height;
		// printf("color=[%u]\n", texture.color);
		my_mlx_pixel_put(&data->bg1, (*ray)->wall_start.x, y++, texture.color);
		texture.tex_pos += texture.tex_step;
	}
}

void	animate_door(t_data *data, t_door **door)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < 150)
	{
		x = (*door)->frame_count;
		while (x < (*door)->frame_count + 165)
		{
			color = get_color(&data->sprite_door, x, y);
			if (color != 0x00000000)
				my_mlx_pixel_put(&(*door)->frame_door, x
					- (*door)->frame_count, y, color);
			x++;
		}
		y++;
	}
}

void	animate_reverse_door(t_data *data, t_door **door)
{
	int		x;
	int		y;
	unsigned int	color;

	clear_image(&(*door)->frame_door, BLACK);
	y = 0;
	while (y < 150)
	{
		x = 0;
		while (x < 165)
		{
			if ((*door)->reverse_frame - x < 0)
				break;
			color = get_color(&data->sprite_door, (*door)->reverse_frame - x, y);
			if (color != 0x00000000)
				my_mlx_pixel_put(&(*door)->frame_door, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_door_texture(t_data *data, t_door **door)
{
	t_texture		texture;
	int				y;
	unsigned int	color;

	y = (*door)->ray.wall_start.y;
	if ((*door)->ray.h_dist < (*door)->ray.v_dist)
		texture.wall_x = fmod((*door)->ray.h_intersect.x, TILE_SIZE)
			/ TILE_SIZE;
	else
		texture.wall_x = fmod((*door)->ray.v_intersect.y, TILE_SIZE)
			/ TILE_SIZE;
	texture.tex_x = (int)(texture.wall_x * ((*door)->frame_door.width - 1));
	texture.tex_step = (*door)->frame_door.height / (*door)->ray.wall_strip;
	texture.tex_pos = ((*door)->ray.wall_start.y - screen_height / 2
			+ (*door)->ray.wall_strip / 2) * texture.tex_step;
	while (y < (*door)->ray.wall_end.y)
	{
		texture.tex_y = (int)texture.tex_pos % (*door)->frame_door.height;
		color = get_color(&(*door)->frame_door, texture.tex_x, texture.tex_y);
		if (get_t(color) != 0xFF)
			my_mlx_pixel_put(&data->bg1, (*door)->ray.wall_start.x, y, color);
		texture.tex_pos += texture.tex_step;
		y++;
	}
}

void	project_wall(t_ray **ray, int col)
{
	(*ray)->dist_projection_plane = (screen_width / 2.0) / tan((FOV / 2.0) * PI
			/ 180);
	(*ray)->wall_strip = (TILE_SIZE / (*ray)->distance)
		* (*ray)->dist_projection_plane;
	(*ray)->ceil = (screen_height) / 2 - (*ray)->wall_strip / 2;
	(*ray)->floor = (*ray)->ceil + (*ray)->wall_strip;
	if ((*ray)->ceil < 0)
		(*ray)->ceil = 0;
	if ((*ray)->floor > screen_height)
		(*ray)->floor = screen_height;
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
	(*ray)->floor_end.y = screen_height;
}

void	project_door(t_door **door, int col)
{
	(*door)->ray.dist_projection_plane = (screen_width / 2.0) / tan((FOV / 2.0)
			* PI / 180);
	(*door)->ray.wall_strip = (TILE_SIZE / (*door)->ray.distance)
		* (*door)->ray.dist_projection_plane;
	(*door)->ray.ceil = (screen_height) / 2 - (*door)->ray.wall_strip / 2;
	(*door)->ray.floor = (*door)->ray.ceil + (*door)->ray.wall_strip;
	if ((*door)->ray.ceil < 0)
		(*door)->ray.ceil = 0;
	if ((*door)->ray.floor > screen_height)
		(*door)->ray.floor = screen_height;
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
	(*door)->ray.floor_end.y = screen_height;
}

// void draw_wall_behind_door(t_data *data, int col, t_ray **ray)
// {
//     t_door *door = NULL;
//     int i = 0;
    
//     // Find door in current column
//     while (data->door[i])
//     {
//         if (data->door[i]->col == col && data->door[i]->found_door)
//         {
//             door = data->door[i];
//             break;
//         }
//         i++;
//     }

//     // Always draw wall background
//     // draw_wall_texture(data, ray);
//     // draw_line(data, (*ray)->ceil_start, (*ray)->ceil_end, data->map.c_color, 1);
//     // draw_line(data, (*ray)->floor_start, (*ray)->floor_end, data->map.f_color, 1);

//     // Draw door on top if closer than wall
//     if (door && door->ray.distance < (*ray)->distance)
//         draw_door_texture(data, &door);
// }

void	draw_wall_behind_door(t_data *data, int col, t_ray **ray)
{
	int i = get_the_closest_door(data);
	int i1 = get_next_door(data, i, col);
	while (1)
	{
		if (i != -1)
		{
			data->door[i]->ray.ray_angle = (*ray)->ray_angle;
			if (data->door[i]->ray.distance >= (*ray)->distance)
			{
				// draw_wall_texture(data, ray);
				// draw_line(data, (*ray)->ceil_start, (*ray)->ceil_end, data->map.c_color,
				// 1);
				// draw_line(data, (*ray)->floor_start, (*ray)->floor_end,
				// 	data->map.f_color, 1);
				break;
			}
			else
			{
				draw_line(data, data->door[i]->ray.ceil_start, data->door[i]->ray.ceil_end,
				data->map.c_color, 1);
				draw_line(data, data->door[i]->ray.floor_start, data->door[i]->ray.floor_end,
				data->map.f_color, 1);
				if (i1 != -1)
				{
					draw_line(data, data->door[i1]->ray.ceil_start, data->door[i1]->ray.ceil_end,
					data->map.c_color, 1);
					draw_line(data, data->door[i1]->ray.floor_start, data->door[i1]->ray.floor_end,
					data->map.f_color, 1);
				}
			}
			// draw_wall_texture(data, ray);
			if (i1 != -1)
				draw_door_texture(data, &data->door[i1]);
			draw_door_texture(data, &data->door[i]);
		}
		break;
	}
}
	// (*door)->ray.ray_angle = (*ray)->ray_angle;
	// // project_door(door, col);
	// if ((*door)->ray.distance >= (*ray)->distance)
	// {
	// 	draw_wall_texture(data, ray);
	// 	draw_line(data, (*ray)->ceil_start, (*ray)->ceil_end, data->map.c_color,
	// 		1);
	// 	draw_line(data, (*ray)->floor_start, (*ray)->floor_end,
	// 		data->map.f_color, 1);
	// }
	// else
	// {
	// 	draw_line(data, (*door)->ray.ceil_start, (*door)->ray.ceil_end,
	// 		data->map.c_color, 1);
	// 	draw_line(data, (*door)->ray.floor_start, (*door)->ray.floor_end,
	// 		data->map.f_color, 1);
	// 	draw_wall_texture(data, ray);
	// 	draw_door_texture(data, door, ray);
	// }
// void	draw_wall_behind_door(t_data *data, int col, t_ray **ray, t_door **door)
// {
// 	(*door)->ray.ray_angle = (*ray)->ray_angle;
// 	project_door(door, col);
// 	if ((*door)->ray.distance >= (*ray)->distance)
// 	{
// 		draw_wall_texture(data, ray);
// 		draw_line(data, (*ray)->ceil_start, (*ray)->ceil_end, data->map.c_color,
// 			1);
// 		draw_line(data, (*ray)->floor_start, (*ray)->floor_end,
// 			data->map.f_color, 1);
// 	}
// 	else
// 	{
// 		draw_line(data, (*door)->ray.ceil_start, (*door)->ray.ceil_end,
// 			data->map.c_color, 1);
// 		draw_line(data, (*door)->ray.floor_start, (*door)->ray.floor_end,
// 			data->map.f_color, 1);
// 		draw_wall_texture(data, ray);
// 		draw_door_texture(data, door, ray);
// 	}
// }

void	project_doors(t_data *data, int col)
{
	int i = 0;
	while (data->door[i])
	{
		// if ((data->door[i])->col == col && data->door[i]->found_door)
		project_door(&data->door[i], col);
		i++;
	}
}

void	wall_projection(t_data *data, t_ray *ray, int col)
{
	// int i = 0;
	project_wall(&ray, col);
	draw_wall_texture(data, &ray);
	draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
	draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
	project_doors(data, col);
	draw_wall_behind_door(data, col, &ray);
	// else
	// {
	// 	draw_wall_texture(data, &ray);
	// 	draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
	// 	draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
	// }
}
// void	wall_projection(t_data *data, t_ray *ray, int col, t_door *door)
// {
// 	int i = 0;
// 	project_wall(&ray, col);
// 	while (condition)
// 	{
// 		/* code */
// 	}
	
// 	if (door->found_door)
// 	{
// 		draw_wall_behind_door(data, col, &ray, &door);
// 	}
// 	else
// 	{
// 		draw_wall_texture(data, &ray);
// 		draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
// 		draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
// 	}
// }
