/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:26:45 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 08:35:32 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	init_all_doors(t_door **door, t_ray ray, t_data *data)
{
	t_door *cur_door;

	cur_door = *door;
	while (cur_door)
	{
		cur_door->found_door = 0;
		cur_door->found_door_pixel = 0;
		cur_door->ray.ray_angle = ray.ray_angle ;
		cur_door->ray.angle_step = ray.angle_step;
		cur_door->ray.distance = 0;
		cur_door->ray.player.x = data->player.x;
		cur_door->ray.player.y = data->player.y;
		cur_door->ray.h_intersect.x = 0;
		cur_door->ray.h_intersect.y = 0;
		cur_door->ray.v_intersect.x = 0;
		cur_door->ray.v_intersect.y = 0;
		cur_door->wall_behind_distance = 0;
		cur_door = cur_door->next;
	}
	
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	t_door	*door;
	int		i;

	i = 0;
	door = ft_malloc(sizeof(t_door) * 2, 1);
	ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
	// door->ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
	// init_all_doors(&door, ray, data);
	while (i < data->num_rays)
	{
		init_ray(&ray, data, door);
		ray.wall_type = NONE;
		check_horizontal_intersect(data, &ray, &door, i);
		check_vertical_intersect(data, &ray, &door, i);
		calc_distance(data, &ray, &door, i);
		wall_projection(data, &ray, i, &door);
		ray.ray_angle += ray.angle_step;
		// door = door->next;
		// door->ray = ray;
		// door->ray.ray_angle = ray.ray_angle;
		// door->ray.player.x = data->player.x;
		// door->ray.player.y = data->player.y;
		i++;
	}
}
