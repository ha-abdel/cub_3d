/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:34 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 17:21:34 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_wall(t_data *data, double x, double y)
{
	int		grid_x;
	int		grid_y;
	char	c;

	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= data->map.height
		|| grid_x >= data->map.width)
		return (1);
	c = data->map.map[grid_y][grid_x];
	if (c == '1' || c == ' ' || c == 'P')
		return (1);
	return (0);
}

int	inside_bounds(t_data *data, double x, double y)
{
	(void)data;
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(t_sprite *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len) + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

void	clear_image(t_sprite *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

unsigned int	get_color(t_sprite *img, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(img->addr + (y * img->line_len + x * (img->bpp
					/ 8)));
	return (color);
}
