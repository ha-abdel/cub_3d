/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:28:34 by salahian          #+#    #+#             */
/*   Updated: 2025/07/23 16:27:50 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	put_the_pixel_in_img(t_data *data, t_point rot)
{
	t_point	pxy;
	double	d;

	pxy.x = data->mini_map.centre.x + (int)rot.x;
	pxy.y = data->mini_map.centre.y + (int)rot.y;
	d = (pxy.x - data->mini_map.centre.x) * (pxy.x - data->mini_map.centre.x)
		+ (pxy.y - data->mini_map.centre.y) * (pxy.y - data->mini_map.centre.y);
	if (d <= data->mini_map.r2)
		my_mlx_pixel_put(&data->bg1, pxy.x, pxy.y, data->mini_map.color);
}

void	rotate_the_map(t_data *data, t_point wxy, t_point dxy)
{
	t_point	rel;
	double	cos_a;
	double	sin_a;
	t_point	rot;

	rel.x = (wxy.x + dxy.x) - data->player.x;
	rel.y = (wxy.y + dxy.y) - data->player.y;
	cos_a = -sin(data->player.angle);
	sin_a = -cos(data->player.angle);
	rot.x = (rel.x * cos_a) - (rel.y * sin_a);
	rot.y = (rel.x * sin_a) + (rel.y * cos_a);
	put_the_pixel_in_img(data, rot);
}

void	help_minimap_walls_rotated(t_data *data, t_point cor)
{
	t_point	dxy;
	t_point	wxy;

	wxy.x = cor.x * TILE_SIZE;
	wxy.y = cor.y * TILE_SIZE;
	if (data->map.map[(int)cor.y][(int)cor.x] == '1')
		data->mini_map.color = RED;
	else
		data->mini_map.color = DARK_GRAY;
	dxy.y = 0;
	while (dxy.y < TILE_SIZE)
	{
		dxy.x = 0;
		while (dxy.x < TILE_SIZE)
		{
			rotate_the_map(data, wxy, dxy);
			dxy.x++;
		}
		dxy.y++;
	}
}

void	mdraw_minimap_walls_rotated(t_data *data)
{
	t_point	cor;

	cor.y = 0;
	while (cor.y < data->map.height)
	{
		cor.x = 0;
		while (cor.x < data->map.width)
		{
			help_minimap_walls_rotated(data, cor);
			cor.x++;
		}
		cor.y++;
	}
}

void	draw_circle(t_data *data, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	r2;
	int	thickness;
	int	dist2;

	thickness = 14;
	r2 = radius * radius;
	y = -radius - thickness;
	while (y <= radius + thickness)
	{
		x = -radius - thickness;
		while (x <= radius + thickness)
		{
			dist2 = x * x + y * y;
			if (dist2 >= r2 && dist2 <= r2 + thickness * thickness)
				my_mlx_pixel_put(&data->bg1, cx + x, cy + y, WHITE);
			x++;
		}
		y++;
	}
}

unsigned int	get_color(t_sprite *img, int x, int y)
{
	unsigned int	color;
	
	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return (BLACK);
	color = *(unsigned int *)(img->addr + (y * img->line_len + x * (img->bpp
					/ 8)));
	return (color);
}

void	img_minimap(t_data *data, int px, int py)
{
	int	i;
	int	j;

	i = 0;
	while (i < 40)
	{
		j = 0;
		while (j < 40)
		{
			data->mini_map.color = *(unsigned int *)(data->minimap.addr + (i
						* data->minimap.line_len + j * (data->minimap.bpp
							/ 8)));
			if (data->mini_map.color != 0xFF000000)
				my_mlx_pixel_put(&data->bg1, (px - 20) + j, (py - 20) + i,
					data->mini_map.color);
			else
			{
				data->mini_map.color = get_color(&data->bg1, px + j, py + i);
				my_mlx_pixel_put(&data->bg1, px + j, py + i,
					data->mini_map.color);
			}
			j++;
		}
		i++;
	}
}

void	create_minimap(t_data *data)
{
	draw_circle(data, SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150, 130);
	data->mini_map.centre.x = SCREEN_WIDTH - 150;
	data->mini_map.centre.y = SCREEN_HEIGHT - 150;
	data->mini_map.r2 = 130 * 130;
	mdraw_minimap_walls_rotated(data);
	img_minimap(data, SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150);
}