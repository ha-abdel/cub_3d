/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:06:15 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/08 09:17:03 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	handle_key(int key, t_data *data)
{
	if (key == ESC_KEY)
		data->event.quit = true;
	if (key == O_KEY)
		data->event.open_door = true;
	if (key == W_KEY)
		data->event.up = true;
	if (key == S_KEY)
		data->event.down = true;
	if (key == D_KEY)
		data->event.right = true;
	if (key == A_KEY)
		data->event.left = true;
	if (key == SPACE_KEY)
		data->event.space = true;
	return (0);
}

int	release_key(int key, t_data *data)
{
	if (key == ESC_KEY)
		data->event.quit = false;
	if (key == O_KEY)
		data->event.open_door = false;
	if (key == W_KEY)
		data->event.up = false;
	if (key == S_KEY)
		data->event.down = false;
	if (key == D_KEY)
		data->event.right = false;
	if (key == A_KEY)
		data->event.left = false;
	if (key == SPACE_KEY)
		data->event.space = false;
	return (0);
}

int	handle_mouse(int x, int y, t_data *data)
{
	static int	oldx;

	(void)y;
	if (x < oldx)
		data->player.angle -= data->rotation_speed;
	else if (x > oldx)
		data->player.angle += data->rotation_speed;
	if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	oldx = x;
	return (0);
}
