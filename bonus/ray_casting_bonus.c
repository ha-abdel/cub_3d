/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:26:45 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 10:49:46 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	check_if_open(t_data **data, int index, int horizontal, t_ray *ray)
{
	t_door	*door;
	double	ratio;
	int		text_x;
	int		text_y;
	int		color;

	if (!(*data)->doors || !(*data)->doors[0] || index == -1)
		return (1);
	door = (*data)->doors[index];
	if (horizontal)
		ratio = fmod(ray->h_intersect.x, TILE_SIZE) / (double)TILE_SIZE;
	else
		ratio = fmod(ray->v_intersect.y, TILE_SIZE) / (double)TILE_SIZE;
	text_x = (int)(ratio * door->frame_door.width);
	if (text_x >= door->frame_door.width)
		text_x = door->frame_door.width - 1;
	text_y = door->frame_door.height / 2;
	color = get_color(&door->frame_door, text_x, text_y);
	if (get_t(color))
		return (1);
	return (0);
}

void	reset_hit_info(t_data **data)
{
	ft_memset(&(*data)->hit, 0, sizeof(t_hit));
}

void	init_ray(t_ray *ray, t_data *data)
{
	ray->h_intersect.x = 0;
	ray->h_intersect.y = 0;
	ray->v_intersect.x = 0;
	ray->v_intersect.y = 0;
	ray->angle_step = (FOV * PI / 180.0) / data->num_rays;
	ray->player.x = data->player.x;
	ray->player.y = data->player.y;
	ray->wall_type = NONE;
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		i;

	i = 0;
	ft_memset(data->front_doors, 0, sizeof(int) * data->nb_doors);
	ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
	while (i < data->num_rays)
	{
		init_ray(&ray, data);
		reset_hit_info(&data);
		check_horizontal_intersect(data, &ray);
		check_vertical_intersect(data, &ray);
		calc_distance(data, &ray);
		// print_hit_info(data);
		wall_projection(data, &ray, i);
		ray.ray_angle += ray.angle_step;
		i++;
	}
}