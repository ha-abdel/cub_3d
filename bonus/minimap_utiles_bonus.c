/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utiles_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:33:13 by salahian          #+#    #+#             */
/*   Updated: 2025/09/06 15:33:35 by salahian         ###   ########.fr       */
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
