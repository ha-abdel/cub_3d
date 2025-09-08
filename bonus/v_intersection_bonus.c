/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_intersection_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:12 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 15:30:06 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	find_v_door(t_data *data, t_ray **ray)
{
	int	which_door;

	which_door = get_door_index(data, construct_point((*ray)->v_intersect.x
				- is_facing_left((*ray)->ray_angle), (*ray)->v_intersect.y));
	if (!check_if_open(&data, which_door, 0, *ray))
	{
		data->hit.v_door_index = which_door;
		data->hit.v_hit = 1;
		data->hit.is_v_door = 1;
		return (1);
	}
	return (0);
}

int	find_v_exit(t_data *data, t_ray **ray)
{
	if (is_exit(data, (*ray)->v_intersect.x - is_facing_left((*ray)->ray_angle),
			(*ray)->v_intersect.y))
	{
		data->hit.v_hit = 1;
		data->hit.is_v_exit = 1;
		return (1);
	}
	return (0);
}

void	find_v_wall(t_data *data, t_ray **ray)
{
	while (!is_wall(data, (*ray)->v_intersect.x
			- is_facing_left((*ray)->ray_angle), (*ray)->v_intersect.y)
		&& inside_bounds(data, (*ray)->v_intersect.x, (*ray)->v_intersect.y))
	{
		if (is_door(data, (*ray)->v_intersect.x
				- is_facing_left((*ray)->ray_angle), (*ray)->v_intersect.y))
		{
			if (find_v_door(data, ray))
				return ;
		}
		if (find_v_exit(data, ray))
			return ;
		(*ray)->v_intersect.x += (*ray)->x_step;
		(*ray)->v_intersect.y += (*ray)->y_step;
	}
	data->hit.v_hit = 1;
	data->hit.is_v_wall = 1;
}

void	check_vertical_intersect(t_data *data, t_ray *ray)
{
	double	tan_val;

	normalize_angle(&ray->ray_angle);
	if (is_perpendicular_to_xaxis(ray->ray_angle))
	{
		ray->v_intersect.x = data->player.x;
		if (is_facing_up(ray->ray_angle))
			ray->v_intersect.y = data->player.y + 3000;
		else
			ray->v_intersect.y = data->player.y - 3000;
		return ;
	}
	tan_val = tan(ray->ray_angle);
	calc_first_v_intersect(data, ray, tan_val);
	calc_vertical_step(data, ray, tan_val);
	ray->v_intersect.x = ray->first_x;
	ray->v_intersect.y = ray->first_y;
	find_v_wall(data, &ray);
}
