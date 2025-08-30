/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:13:04 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/30 16:41:49 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	calc_horizontal_dist(t_data *data, t_ray **ray)
{
	data->hit.distance = sqrt(data->hit.h_dist);
	(*ray)->ray_end.x = (*ray)->h_intersect.x;
	(*ray)->ray_end.y = (*ray)->h_intersect.y;
	if (data->hit.is_h_door)
	{
		data->hit.is_door = 1;
		data->hit.door_index = data->hit.h_door_index;
		data->front_doors[data->hit.door_index] = 1;
	}
	else
		data->hit.is_wall = 1;
}
void	calc_vertical_dist(t_data *data, t_ray **ray)
{
	data->hit.distance = sqrt(data->hit.v_dist);
	(*ray)->ray_end.x = (*ray)->v_intersect.x;
	(*ray)->ray_end.y = (*ray)->v_intersect.y;
	if (data->hit.is_v_wall)
		data->hit.is_wall = 1;
	else
	{
		data->hit.is_door = 1;
		data->hit.door_index = data->hit.v_door_index;
		data->front_doors[data->hit.door_index] = 1;
	}
}

void	calc_wall_distance(t_data *data, t_ray **ray)
{
	data->hit.h_dist = pow((*ray)->h_intersect.x - data->player.x, 2)
		+ pow((*ray)->h_intersect.y - data->player.y, 2);
	data->hit.v_dist = pow((*ray)->v_intersect.x - data->player.x, 2)
		+ pow((*ray)->v_intersect.y - data->player.y, 2);
	if (data->hit.h_dist < data->hit.v_dist)
	{
		calc_horizontal_dist(data, ray);
	}
	else
	{
		calc_vertical_dist(data, ray);
	}
	data->hit.distance *= cos((*ray)->ray_angle - data->player.angle);
}

void	calc_distance(t_data *data, t_ray *ray)
{
	calc_wall_distance(data, &ray);
	if (data->hit.is_door)
		draw_line(data, ray->player, ray->ray_end, YELLOW, 2);
	else
		draw_line(data, ray->player, ray->ray_end, BLUE, 2);
}
