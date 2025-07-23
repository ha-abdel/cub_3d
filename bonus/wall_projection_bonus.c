/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:27:24 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 14:52:17 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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
	while (y < (*ray)->wall_end.y)
	{
		texture.tex_y = (int)texture.tex_pos % img.height;
		texture.pixel = img.addr + (texture.tex_y * img.line_len)
			+ (texture.tex_x * (img.bpp / 8));
		texture.color = *(unsigned int *)texture.pixel;
		texture.tex_x = texture.tex_x % img.width;
		texture.tex_y = texture.tex_y % img.height;
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

void	draw_door_texture(t_data *data, t_door **door, t_ray **ray)
{
	t_texture		texture;
	int				y;
	unsigned int	color;

	(void)ray;
	y = (*door)->ray.wall_start.y;
	if ((*door)->ray.h_dist < (*door)->ray.v_dist)
		texture.wall_x = fmod((*door)->ray.h_intersect.x, TILE_SIZE)
			/ TILE_SIZE;
	else
		texture.wall_x = fmod((*door)->ray.v_intersect.y, TILE_SIZE)
			/ TILE_SIZE;
	texture.tex_x = (int)(texture.wall_x * (data->frame_door.width - 1));
	texture.tex_step = data->frame_door.height / (*door)->ray.wall_strip;
	texture.tex_pos = ((*door)->ray.wall_start.y - screen_height / 2
			+ (*door)->ray.wall_strip / 2) * texture.tex_step;
	while (y < (*door)->ray.wall_end.y)
	{
		texture.tex_y = (int)texture.tex_pos % data->frame_door.height;
		color = get_color(&data->frame_door, texture.tex_x, texture.tex_y);
		if (get_t(color) != 0xFF)
			my_mlx_pixel_put(&data->bg1, (*door)->ray.wall_start.x, y, color);
		texture.tex_pos += texture.tex_step;
		y++;
	}
}

void	draw_wall_behind_door(t_data *data, int col, t_ray **ray, t_door **door)
{
	(*door)->ray.ray_angle = (*ray)->ray_angle;
	project_door(door, col);
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
        door->ray.ray_angle = ray->ray_angle;
        project_door(&door, col);

        if (door->ray.distance >= ray->distance)
        {
            // draw_wall_texture(data, ray);
            draw_wall_texture(data, &ray);
			 draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
    		draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
			
        }
        else
        {
			//  draw_line(data, door->ray.ceil_start, door->ray.ceil_end, data->map.c_color, 1);
   			//  draw_line(data, door->ray.floor_start, door->ray.floor_end, data->map.f_color, 1);
			draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
    		draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
			 draw_wall_texture(data, &ray);
			 draw_door_texture(data, &door, &ray);
        }
    }
    else
    {
        draw_wall_texture(data, &ray);
		draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
		draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
	}
}
