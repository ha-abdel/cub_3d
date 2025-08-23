/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:13:04 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/23 11:08:29 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	calc_wall_distance(t_data *data, t_ray **ray)
{
	data->hit.h_dist = pow((*ray)->h_intersect.x - data->player.x, 2)
		+ pow((*ray)->h_intersect.y - data->player.y, 2);
	data->hit.v_dist = pow((*ray)->v_intersect.x - data->player.x, 2)
		+ pow((*ray)->v_intersect.y - data->player.y, 2);
	if (data->hit.h_dist < data->hit.v_dist)
	{
		data->hit.distance = sqrt(data->hit.h_dist);
		(*ray)->ray_end.x = (*ray)->h_intersect.x;
		(*ray)->ray_end.y = (*ray)->h_intersect.y;
		if (data->hit.is_h_door)
		{
			data->hit.is_door = 1;
			data->hit.door_index = data->hit.h_dist;
		}
		else
			data->hit.is_wall = 1;
	}
	else
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
		}
	}
	data->hit.distance *= cos((*ray)->ray_angle - data->player.angle);
}

// void	calc_door_distance(t_data *data)
// {
// 	int h_i = data->hit.h_door_index;
// 	int v_i = data->hit.v_door_index;
// 	if (data->hit.h_hit)
// 		data->hit.h_dist = pow(data->doors[h_i]->ray.h_intersect.x - data->player.x,
// 				2) + pow(data->doors[h_i]->ray.h_intersect.y - data->player.y, 2);
// 	else
// 		data->hit.h_dist = INFINITY;
// 	if (data->hit.v_hit)
// 		data->hit.v_dist = pow(data->doors[v_i]->ray.v_intersect.x - data->player.x,
// 				2) + pow(data->doors[v_i]->ray.v_intersect.y - data->player.y, 2);
// 	else
// 		data->hit.v_dist = INFINITY;
// 	if (data->hit.h_dist < data->hit.v_dist)
// 	{
// 		data->hit.door_index = h_i;
// 		data->hit.distance = sqrt(data->hit.h_dist);
// 		data->doors[h_i]->ray.ray_end.x = data->doors[h_i]->ray.h_intersect.x;
// 		data->doors[h_i]->ray.ray_end.y = data->doors[h_i]->ray.h_intersect.y;
// 	}
// 	else
// 	{
// 		data->hit.door_index = v_i;
// 		data->hit.distance = sqrt(data->hit.v_dist);
// 		data->doors[v_i]->ray.ray_end.x = data->doors[v_i]->ray.v_intersect.x;
// 		data->doors[v_i]->ray.ray_end.y = data->doors[v_i]->ray.v_intersect.y;
// 	}
// 	data->hit.distance *= cos(data->doors[h_i]->ray.ray_angle - data->player.angle);
// }
// void	calc_door_distance(t_data *data, t_door **door)
// {
// 	if ((*door)->ray.h_intersect.x != 0 || (*door)->ray.h_intersect.y != 0)
// 		(*door)->ray.h_dist = pow((*door)->ray.h_intersect.x - data->player.x,
// 				2) + pow((*door)->ray.h_intersect.y - data->player.y, 2);
// 	else
// 		(*door)->ray.h_dist = INFINITY;
// 	if ((*door)->ray.v_intersect.x != 0 || (*door)->ray.v_intersect.y != 0)
// 		(*door)->ray.v_dist = pow((*door)->ray.v_intersect.x - data->player.x,
// 				2) + pow((*door)->ray.v_intersect.y - data->player.y, 2);
// 	else
// 		(*door)->ray.v_dist = INFINITY;
// 	if ((*door)->ray.h_dist < (*door)->ray.v_dist)
// 	{
// 		(*door)->ray.distance = sqrt((*door)->ray.h_dist);
// 		(*door)->ray.ray_end.x = (*door)->ray.h_intersect.x;
// 		(*door)->ray.ray_end.y = (*door)->ray.h_intersect.y;
// 	}
// 	else
// 	{
// 		(*door)->ray.distance = sqrt((*door)->ray.v_dist);
// 		(*door)->ray.ray_end.x = (*door)->ray.v_intersect.x;
// 		(*door)->ray.ray_end.y = (*door)->ray.v_intersect.y;
// 	}
// 	(*door)->ray.distance *= cos((*door)->ray.ray_angle - data->player.angle);
// }

void	calc_distance(t_data *data, t_ray *ray)
{
	// if (data->hit.is_wall)
		calc_wall_distance(data, &ray);
	// else
	// {
	// 	calc_door_distance(data);
	// }
	if (data->hit.is_door)
		draw_line(data, ray->player, ray->ray_end, YELLOW, 2);
	else 
		draw_line(data, ray->player, ray->ray_end, BLUE, 2);
	// if (door->found_door)
	// 	draw_line(data, door->ray.player, door->ray.ray_end, YELLOW, 2);
}
