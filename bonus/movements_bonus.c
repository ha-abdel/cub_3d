/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:05 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 15:20:35 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"
#include <stdbool.h>

bool	is_valid_move(t_data *data, double x, double y)
{
	double	safety;

	safety = 6;
	if (is_wall(data, x, y) || (is_door(data, x, y)
			&& (data->doors[get_door_index(data, construct_point(x,
							y))]->open == 0)))
		return (false);
	if (is_wall(data, x + safety, y) || (is_door(data, x + safety, y)
			&& (data->doors[get_door_index(data, construct_point(x + safety,
							y))]->open == 0)))
		return (false);
	if (is_wall(data, x - safety, y) || (is_door(data, x - safety, y)
			&& (data->doors[get_door_index(data, construct_point(x - safety,
							y))]->open == 0)))
		return (false);
	if (is_wall(data, x, y + safety) || (is_door(data, x, y + safety)
			&& (data->doors[get_door_index(data, construct_point(x,
							y + safety))]->open == 0)))
		return (false);
	if (is_wall(data, x, y - safety) || (is_door(data, x, y - safety)
			&& (data->doors[get_door_index(data, construct_point(x,
							y - safety))]->open == 0)))
		return (false);
	return (true);
}

void	check_collision(t_data *data, double old_px, double old_py)
{
	if (!is_valid_move(data, data->player.x, data->player.y))
	{
		data->player.x = old_px;
		data->player.y = old_py;
	}
	else if (is_exit(data, data->player.x, data->player.y))
	{
		printf("you found the exit\n");
		destroy_window(data);
	}
}

void	move_player(t_data *data)
{
	if (data->event.up == true)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle);
		data->player.y += PLAYER_SPEED * sin(data->player.angle);
	}
	if (data->event.down == true)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle + M_PI);
		data->player.y += PLAYER_SPEED * sin(data->player.angle + M_PI);
	}
	if (data->event.left == true)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle - M_PI_2);
		data->player.y += PLAYER_SPEED * sin(data->player.angle - M_PI_2);
	}
	if (data->event.right == true)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle + M_PI_2);
		data->player.y += PLAYER_SPEED * sin(data->player.angle + M_PI_2);
	}
}
