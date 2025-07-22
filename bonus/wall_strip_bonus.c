/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_strip_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:36:01 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/22 08:36:57 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	project_wall(t_ray **ray, int col)
{
	(*ray)->dist_projection_plane = (SCREEN_WIDTH / 2.0) / tan((FOV / 2.0) * PI
			/ 180);
	(*ray)->wall_strip = (TILE_SIZE / (*ray)->distance)
		* (*ray)->dist_projection_plane;
	(*ray)->ceil = (SCREEN_HEIGHT) / 2 - (*ray)->wall_strip / 2;
	(*ray)->floor = (*ray)->ceil + (*ray)->wall_strip;
	if ((*ray)->ceil < 0)
		(*ray)->ceil = 0;
	if ((*ray)->floor > SCREEN_HEIGHT)
		(*ray)->floor = SCREEN_HEIGHT;
	(*ray)->wall_start.x = col;
	(*ray)->wall_start.y = (*ray)->ceil;
	(*ray)->wall_end.x = col;
	(*ray)->wall_end.y = (*ray)->floor;
	(*ray)->ceil_start.x = col;
	(*ray)->ceil_start.y = 0;
	(*ray)->ceil_end.x = col;
	(*ray)->ceil_end.y = (*ray)->ceil - 1;
	(*ray)->floor_start.x = col;
	(*ray)->floor_start.y = (*ray)->ceil + (*ray)->wall_strip;
	(*ray)->floor_end.x = col;
	(*ray)->floor_end.y = SCREEN_HEIGHT;
}

void	project_door(t_door **door, int col)
{
	(*door)->ray.dist_projection_plane = (SCREEN_WIDTH / 2.0) / tan((FOV / 2.0)
			* PI / 180);
	(*door)->ray.wall_strip = (TILE_SIZE / (*door)->ray.distance)
		* (*door)->ray.dist_projection_plane;
	(*door)->ray.ceil = (SCREEN_HEIGHT) / 2 - (*door)->ray.wall_strip / 2;
	(*door)->ray.floor = (*door)->ray.ceil + (*door)->ray.wall_strip;
	if ((*door)->ray.ceil < 0)
		(*door)->ray.ceil = 0;
	if ((*door)->ray.floor > SCREEN_HEIGHT)
		(*door)->ray.floor = SCREEN_HEIGHT;
	(*door)->ray.wall_start.x = col;
	(*door)->ray.wall_start.y = (*door)->ray.ceil;
	(*door)->ray.wall_end.x = col;
	(*door)->ray.wall_end.y = (*door)->ray.floor;
	(*door)->ray.ceil_start.x = col;
	(*door)->ray.ceil_start.y = 0;
	(*door)->ray.ceil_end.x = col;
	(*door)->ray.ceil_end.y = (*door)->ray.ceil - 1;
	(*door)->ray.floor_start.x = col;
	(*door)->ray.floor_start.y = (*door)->ray.ceil + (*door)->ray.wall_strip;
	(*door)->ray.floor_end.x = col;
	(*door)->ray.floor_end.y = SCREEN_HEIGHT;
}
