/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:30:56 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 17:21:22 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	calc_first_h_intersect(t_data *data, t_ray *ray, double tan_val)
{
	if (is_facing_up(ray->ray_angle))
		ray->first_y = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	else
		ray->first_y = (floor(data->player.y / TILE_SIZE) + 1) * TILE_SIZE;
	ray->first_x = data->player.x + (ray->first_y - data->player.y) / tan_val;
}

void	calc_horizontal_step(t_data *data, t_ray *ray, double tan_val)
{
	(void)data;
	if (is_facing_up(ray->ray_angle))
		ray->y_step = -TILE_SIZE;
	else
		ray->y_step = TILE_SIZE;
	ray->x_step = TILE_SIZE / fabs(tan_val);
	if (is_facing_left(ray->ray_angle))
		ray->x_step = -(ray->x_step);
}

double	handle_division_by_zero(double angle)
{
	double	tan_val;

	tan_val = tan(angle);
	if (fabs(tan_val) <= 0.000001)
	{
		if (tan_val >= 0)
			tan_val = 0.000001;
		else
			tan_val = -0.000001;
	}
	return (tan_val);
}

void	check_horizontal_intersect(t_data *data, t_ray *ray)
{
	double	tan_val;

	normalize_angle(&ray->ray_angle);
	if (is_perpendicular_to_yaxis(ray->ray_angle))
	{
		if (is_facing_right(ray->ray_angle))
			(ray->h_intersect).x = data->player.x + 3000;
		else
			(ray->h_intersect).x = data->player.x - 3000;
		(ray->h_intersect).y = data->player.y;
		return ;
	}
	tan_val = handle_division_by_zero(ray->ray_angle);
	calc_first_h_intersect(data, ray, tan_val);
	calc_horizontal_step(data, ray, tan_val);
	(ray->h_intersect).x = ray->first_x;
	(ray->h_intersect).y = ray->first_y;
	while (!is_wall(data, (ray->h_intersect).x, (ray->h_intersect).y
			- is_facing_up(ray->ray_angle)) && inside_bounds(data,
			(ray->h_intersect).x, (ray->h_intersect).y))
	{
		(ray->h_intersect).x += ray->x_step;
		(ray->h_intersect).y += ray->y_step;
	}
}
