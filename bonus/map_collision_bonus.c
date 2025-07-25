/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collision_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:30:28 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/21 18:30:29 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	is_door(t_data *data, double x, double y)
{
	int		grid_x;
	int		grid_y;
	char	c;

	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= data->map.height
		|| grid_x >= data->map.width)
		return (0);
	c = data->map.map[grid_y][grid_x];
	if (c == 'D')
		return (1);
	return (0);
}

int	is_wall(t_data *data, double x, double y)
{
	int		grid_x;
	int		grid_y;
	char	c;

	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= data->map.height
		|| grid_x >= data->map.width)
		return (0);
	c = data->map.map[grid_y][grid_x];
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}
