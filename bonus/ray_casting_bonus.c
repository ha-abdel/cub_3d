/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:26:45 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/23 11:09:32 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	init_all_doors(t_data **data, t_ray *ray)
{
	int	i;

	i = 0;
	while ((*data)->doors[i])
	{
		(*data)->doors[i]->ray.ray_angle = ray->ray_angle;
		// (*data)->doors[i]->open = 1;
		i++;
	}
	
}

void	reset_hit_info(t_data **data)
{
	(*data)->hit.is_door = 0;
	(*data)->hit.is_wall = 0;
	(*data)->hit.is_h_wall = 0;
	(*data)->hit.is_v_wall = 0;
	(*data)->hit.is_h_door = 0;
	(*data)->hit.is_v_door = 0;
	(*data)->hit.h_hit = 0;
	(*data)->hit.v_hit = 0;
	(*data)->hit.door_index = 0;
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		i;

	i = 0;
	// ray.ray_angle = data->player.angle;
	ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
	while (i < data->num_rays)
	{
		
		init_ray(&ray, data);
		init_all_doors(&data, &ray);
		reset_hit_info(&data);
		check_horizontal_intersect(data, &ray);
		check_vertical_intersect(data, &ray);
		calc_distance(data, &ray);
		// print_hit_info(data);
		wall_projection(data, &ray, i);
		ray.ray_angle += ray.angle_step;
		// door.ray.ray_angle = ray.ray_angle;
		i++;
	}
}
// void	cast_rays(t_data *data)
// {
// 	t_ray	ray;
// 	t_door	door;
// 	int		i;

// 	i = 0;
// 	ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
// 	door.ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
// 	while (i < data->num_rays)
// 	{
// 		init_ray(&ray, data);
// 		init_ray(&door.ray, data);
// 		ray.wall_type = NONE;
// 		check_horizontal_intersect(data, &ray, &door);
// 		check_vertical_intersect(data, &ray, &door);
// 		calc_distance(data, &ray, &door);
// 		wall_projection(data, &ray, i, &door);
// 		ray.ray_angle += ray.angle_step;
// 		door.ray.ray_angle = ray.ray_angle;
// 		i++;
// 	}
// }
