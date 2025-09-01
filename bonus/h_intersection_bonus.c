/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersection_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/01 09:18:42 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


// int	check_if_open(t_data **data, int index, int horizontal, t_ray *ray)
// {
// 	t_door	*door;
// 	double	ratio;
// 	int		text_x;
// 	int		text_y;
// 	int		color;

// 	if (!(*data)->doors || !(*data)->doors[0] || index == -1)
// 		return (1);
// 	door = (*data)->doors[index];
// 	if (horizontal)
// 		ratio = fmod(ray->h_intersect.x, TILE_SIZE) / (double)TILE_SIZE;
// 	else
// 		ratio = fmod(ray->v_intersect.y, TILE_SIZE) / (double)TILE_SIZE;
// 	text_x = (int)(ratio * door->frame_door.width);
// 	if (text_x >= door->frame_door.width)
// 		text_x = door->frame_door.width - 1;
// 	text_y = door->frame_door.height / 2;
// 	color = get_color(&door->frame_door, text_x, text_y);
// 	if (get_t(color))
// 		return (1);
// 	return (0);
// }

int	find_h_door(t_data *data, t_ray **ray)
{
	int	which_door;

	which_door = get_door_index(data, construct_point((*ray)->h_intersect.x,
				(*ray)->h_intersect.y - is_facing_up((*ray)->ray_angle)));
	if (!check_if_open(&data, which_door, 1, *ray))
	{
		data->hit.h_door_index = which_door;
		data->hit.h_hit = 1;
		data->hit.is_h_door = 1;
		return (1);
	}
	return (0);
}
int	find_h_exit(t_data *data, t_ray **ray)
{
	
	if (is_exit(data, (*ray)->h_intersect.x, (*ray)->h_intersect.y - is_facing_up((*ray)->ray_angle)))
	{
		data->hit.h_hit = 1;
		data->hit.is_h_exit = 1;
		return (1);
	}
	return (0);
}

void	find_h_wall(t_data *data, t_ray **ray)
{
	while (!is_wall(data, ((*ray)->h_intersect).x, ((*ray)->h_intersect).y
			- is_facing_up((*ray)->ray_angle)) && inside_bounds(data,
			((*ray)->h_intersect).x, ((*ray)->h_intersect).y))
	{
		if (is_door(data, ((*ray)->h_intersect).x, ((*ray)->h_intersect).y
				- is_facing_up((*ray)->ray_angle)))
		{
			if (find_h_door(data, ray))
				return ;
		}
		if (find_h_exit(data, ray))
				return ;
		((*ray)->h_intersect).x += (*ray)->x_step;
		((*ray)->h_intersect).y += (*ray)->y_step;
	}
	data->hit.h_hit = 1;
	data->hit.is_h_wall = 1;
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
