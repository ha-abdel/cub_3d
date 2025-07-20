/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:55 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 15:47:46 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		i;
	int		color;

	i = 0;
	init_ray(&ray, data);
	while (i < data->num_rays)
	{
		ray.wall_type = NONE;
		check_horizontal_intersect(data, &ray);
		check_vertical_intersect(data, &ray);
		calc_distance(data, &ray, &color);
		wall_projection(data, &ray, &color, i);
		ray.ray_angle += ray.angle_step;
		i++;
	}
}
