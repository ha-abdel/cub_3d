/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_intersection_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:12 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 14:46:54 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	calc_first_v_intersect(t_data *data, t_ray *ray, double tan_val)
{
	if (is_facing_right(ray->ray_angle))
		ray->first_x = (floor(data->player.x / TILE_SIZE) + 1) * TILE_SIZE;
	else
		ray->first_x = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	ray->first_y = data->player.y + (ray->first_x - data->player.x) * tan_val;
}

void	calc_vertical_step(t_data *data, t_ray *ray, double tan_val)
{
	(void)data;
	if (is_facing_right(ray->ray_angle))
		ray->x_step = TILE_SIZE;
	else
		ray->x_step = -TILE_SIZE;
	ray->y_step = TILE_SIZE * fabs(tan_val);
	if (is_facing_up(ray->ray_angle))
		ray->y_step = -ray->y_step;
}

void	find_v_wall(t_data *data, t_ray **ray, int col)
{
	int index = 0;
	while (!is_wall(data, (*ray)->v_intersect.x
			- is_facing_left((*ray)->ray_angle), (*ray)->v_intersect.y)
		&& inside_bounds(data, (*ray)->v_intersect.x, (*ray)->v_intersect.y))
	{
		if (is_door(data, (*ray)->v_intersect.x - is_facing_left((*ray)->ray_angle), (*ray)->v_intersect.y))
		{
			index = get_current_door(data, (*ray)->v_intersect.x - is_facing_left((*ray)->ray_angle), (*ray)->v_intersect.y);
			data->door[index]->found_door = 1;
			data->door[index]->ray.v_intersect.x = (*ray)->v_intersect.x;
			data->door[index]->ray.v_intersect.y = (*ray)->v_intersect.y;
			data->door[index]->col = col;
		}
		(*ray)->v_intersect.x += (*ray)->x_step;
		(*ray)->v_intersect.y += (*ray)->y_step;
	}
}

void	check_vertical_intersect(t_data *data, t_ray *ray, int col)
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
	find_v_wall(data, &ray, col);
}
