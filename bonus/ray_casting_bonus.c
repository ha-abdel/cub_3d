/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:26:45 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 15:52:26 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

// void	init_all_doors(t_door **door, t_ray ray, t_data *data)
// {
// 	t_door *cur_door;

// 	cur_door = *door;
// 	while (cur_door)
// 	{
// 		cur_door->found_door = 0;
// 		cur_door->found_door_pixel = 0;
// 		cur_door->ray.ray_angle = ray.ray_angle ;
// 		cur_door->ray.angle_step = ray.angle_step;
// 		cur_door->ray.distance = 0;
// 		cur_door->ray.player.x = data->player.x;
// 		cur_door->ray.player.y = data->player.y;
// 		cur_door->ray.h_intersect.x = 0;
// 		cur_door->ray.h_intersect.y = 0;
// 		cur_door->ray.v_intersect.x = 0;
// 		cur_door->ray.v_intersect.y = 0;
// 		cur_door->wall_behind_distance = 0;
// 		cur_door = cur_door->next;
// 	}
	
// }


void	cast_rays(t_data *data)
{
	t_ray	ray;
	// t_door	door;
	int		i;

	i = 0;
	
	ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
	// door.ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
	init_ray(&ray, data);
	while (i < data->num_rays)
	{
		ray.wall_type = NONE;
		check_horizontal_intersect(data, &ray, i);
		check_vertical_intersect(data, &ray, i);
		calc_distance(data, &ray, i);
		wall_projection(data, &ray, i);
		ray.ray_angle += ray.angle_step;
		// door.ray.ray_angle = ray.ray_angle;
		i++;
	}
}
