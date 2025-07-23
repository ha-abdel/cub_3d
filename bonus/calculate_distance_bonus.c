/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:13:04 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 15:55:01 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	calc_wall_distance(t_data *data, t_ray **ray)
{
	(*ray)->h_dist = pow((*ray)->h_intersect.x - data->player.x, 2)
		+ pow((*ray)->h_intersect.y - data->player.y, 2);
	(*ray)->v_dist = pow((*ray)->v_intersect.x - data->player.x, 2)
		+ pow((*ray)->v_intersect.y - data->player.y, 2);
	if ((*ray)->h_dist < (*ray)->v_dist)
	{
		(*ray)->distance = sqrt((*ray)->h_dist);
		(*ray)->ray_end.x = (*ray)->h_intersect.x;
		(*ray)->ray_end.y = (*ray)->h_intersect.y;
	}
	else
	{
		(*ray)->distance = sqrt((*ray)->v_dist);
		(*ray)->ray_end.x = (*ray)->v_intersect.x;
		(*ray)->ray_end.y = (*ray)->v_intersect.y;
	}
	(*ray)->distance *= cos((*ray)->ray_angle - data->player.angle);
}

void	calc_door_distance(t_data *data, t_door **door)
{
	if ((*door)->ray.h_intersect.x != 0 || (*door)->ray.h_intersect.y != 0)
		(*door)->ray.h_dist = pow((*door)->ray.h_intersect.x - data->player.x,
				2) + pow((*door)->ray.h_intersect.y - data->player.y, 2);
	else
		(*door)->ray.h_dist = INFINITY;
	if ((*door)->ray.v_intersect.x != 0 || (*door)->ray.v_intersect.y != 0)
		(*door)->ray.v_dist = pow((*door)->ray.v_intersect.x - data->player.x,
				2) + pow((*door)->ray.v_intersect.y - data->player.y, 2);
	else
		(*door)->ray.v_dist = INFINITY;
	if ((*door)->ray.h_dist < (*door)->ray.v_dist)
	{
		(*door)->ray.distance = sqrt((*door)->ray.h_dist);
		(*door)->ray.ray_end.x = (*door)->ray.h_intersect.x;
		(*door)->ray.ray_end.y = (*door)->ray.h_intersect.y;
	}
	else
	{
		
		(*door)->ray.distance = sqrt((*door)->ray.v_dist);
		(*door)->ray.ray_end.x = (*door)->ray.v_intersect.x;
		(*door)->ray.ray_end.y = (*door)->ray.v_intersect.y;
	}
	(*door)->ray.distance *= cos((*door)->ray.ray_angle - data->player.angle);
}



void	calc_distance(t_data *data, t_ray *ray, int col)
{
	int i = 0;
	calc_wall_distance(data, &ray);
	while (data->door[i])
	{
		// init_door(data, &data->door[i], ray, col);
		if (data->door[i]->col = col && data->door[i]->found_door)
			calc_door_distance(data, &data->door[i]);
	}
	draw_line(data, ray->player, ray->ray_end, BLUE, 2);
	// if (door->found_door)
	// 	draw_line(data, door->ray.player, door->ray.ray_end, YELLOW, 2);
}
