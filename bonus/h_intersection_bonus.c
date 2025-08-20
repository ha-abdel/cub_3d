/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersection_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/20 13:05:20 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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
int	check_if_open(t_data **data, int index, int horizontal)
{
	int text_x;
	int text_y;
	t_door *door;
	int color;
	
	if (!(*data)->doors || !(*data)->doors[0] || index == -1)
		return (1);
	door = (*data)->doors[index];
	if (horizontal)
		text_x = fmod(door->ray.h_intersect.x, TILE_SIZE) / TILE_SIZE;
	else
		text_x = fmod(door->ray.h_intersect.y, TILE_SIZE) / TILE_SIZE;
	text_x *= (door->frame_door.width);
	text_y = door->frame_door.height / 2;
	color = get_color(&door->frame_door, text_x, text_y);
	if (get_t(color))
		return (1);
	return (0);
	
}

int	get_door_index(t_data *data, t_point p)
{
	int	i;

	i = 0;
	while (data && data->doors && data->doors[i])
	{
		if (data->doors[i]->col  == (int)(p.x / TILE_SIZE) && 
			data->doors[i]->row  == (int)(p.y / TILE_SIZE))
				return i;
		i++;
	}
	return (-1);
	
}
void	find_h_wall(t_data *data, t_ray **ray)
{
	int	which_door;
	while (!is_wall(data, ((*ray)->h_intersect).x, ((*ray)->h_intersect).y
			- is_facing_up((*ray)->ray_angle)) && inside_bounds(data,
			((*ray)->h_intersect).x, ((*ray)->h_intersect).y))
	{
		if (is_door(data, ((*ray)->h_intersect).x, ((*ray)->h_intersect).y
				- is_facing_up((*ray)->ray_angle)))
		{
			which_door = get_door_index(data,
						construct_point((*ray)->h_intersect.x, (*ray)->h_intersect.y - is_facing_up((*ray)->ray_angle)));
			if (!check_if_open(&data, which_door, 1))
			{
				data->hit.h_door_index = which_door;
				data->hit.h_hit = 1;
				data->hit.is_door = 1;
				return ;
			}
		}
		((*ray)->h_intersect).x += (*ray)->x_step;
		((*ray)->h_intersect).y += (*ray)->y_step;
	}
	if (data->hit.is_door)
	{
		data->hit.h_hit = 1;
		data->hit.is_wall = 1;
	}
	
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
			(ray->h_intersect).x = data->player.x + MAX_RAY_DISTANCE;
		else
			(ray->h_intersect).x = data->player.x - MAX_RAY_DISTANCE;
		(ray->h_intersect).y = data->player.y;
		return ;
	}
	tan_val = handle_division_by_zero(ray->ray_angle);
	calc_first_h_intersect(data, ray, tan_val);
	calc_horizontal_step(data, ray, tan_val);
	(ray->h_intersect).x = ray->first_x;
	(ray->h_intersect).y = ray->first_y;
	find_h_wall(data, &ray);
}
