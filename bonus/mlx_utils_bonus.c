/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:15:01 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 10:44:23 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	inside_bounds(t_data *data, double x, double y)
{
	(void)data;
	if (x < 0 || x >= screen_width || y < 0 || y >= screen_height)
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
