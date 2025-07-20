/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:51:43 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 17:25:39 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

void	wall_projection(t_data *data, t_ray *ray, int *color, int col)
{
	(void)color;
	ray->dist_projection_plane = (SCREEN_WIDTH / 2.0) / tan((FOV / 2.0) * PI
			/ 180);
	ray->wall_strip = (TILE_SIZE / ray->distance) * ray->dist_projection_plane;
	ray->ceil = (SCREEN_HEIGHT) / 2 - ray->wall_strip / 2;
	ray->floor = ray->ceil + ray->wall_strip;
	if (ray->ceil < 0)
		ray->ceil = 0;
	if (ray->floor > SCREEN_HEIGHT)
		ray->floor = SCREEN_HEIGHT;
	ray->wall_start.x = col;
	ray->wall_start.y = ray->ceil;
	ray->wall_end.x = col;
	ray->wall_end.y = ray->floor;
	ray->ceil_start.x = col;
	ray->ceil_start.y = 0;
	ray->ceil_end.x = col;
	ray->ceil_end.y = ray->ceil - 1;
	ray->floor_start.x = col;
	ray->floor_start.y = ray->ceil + ray->wall_strip;
	ray->floor_end.x = col;
	ray->floor_end.y = SCREEN_HEIGHT;
	draw_wall_texture(data, ray);
	draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
	draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
}
