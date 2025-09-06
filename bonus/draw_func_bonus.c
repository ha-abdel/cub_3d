/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:00 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 14:58:08 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	draw_line(t_data *data, t_point start_p, t_point end_p, int color)
{
	t_point	point;
	double	dx;
	double	dy;
	double	steps;
	int		i;

	dx = end_p.x - start_p.x;
	dy = end_p.y - start_p.y;
	steps = fmax(fabs(dx), fabs(dy));
	steps = fmin(steps, data->max_dist_pixel);
	point.x = start_p.x;
	point.y = start_p.y;
	i = 0;
	while (i < steps)
	{
		my_mlx_pixel_put(&data->bg1, (int)point.x, (int)point.y, color);
		i++;
		point.x += dx / steps;
		point.y += dy / steps;
	}
}
