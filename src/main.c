/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:38:56 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 15:24:00 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	move_player(t_data *data, int key)
{
	if (key == W_KEY)
	{
		data->player.x += cos(data->player.angle) * PLAYER_SPEED;
		data->player.y += sin(data->player.angle) * PLAYER_SPEED;
	}
	if (key == S_KEY)
	{
		data->player.x += cos(data->player.angle + M_PI) * PLAYER_SPEED;
		data->player.y += sin(data->player.angle + M_PI) * PLAYER_SPEED;
	}
	if (key == A_KEY)
	{
		data->player.x += cos(data->player.angle - M_PI_2) * PLAYER_SPEED;
		data->player.y += sin(data->player.angle - M_PI_2) * PLAYER_SPEED;
	}
	if (key == D_KEY)
	{
		data->player.x += cos(data->player.angle + M_PI_2) * PLAYER_SPEED;
		data->player.y += sin(data->player.angle + M_PI_2) * PLAYER_SPEED;
	}
}

void	rotate_player(t_data *data, int key)
{
	if (key == LEFT_ARROW)
	{
		data->player.angle -= data->rotation_speed;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
	if (key == RIGHT_ARROW)
	{
		data->player.angle += data->rotation_speed;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}
}

int	handle_key(int key, t_data *data)
{
	double	old_px;
	double	old_py;

	old_px = data->player.x;
	old_py = data->player.y;
	if (key == ESC_KEY)
		destroy_window(data);
	move_player(data, key);
	if (is_wall(data, data->player.x - is_facing_left(data->player.angle),
			data->player.y - is_facing_up(data->player.angle)))
	{
		data->player.x = old_px;
		data->player.y = old_py;
	}
	rotate_player(data, key);
	return (0);
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (1);
	initial_data(&data);
	if (!main_function_parsing(&data, av[1]))
		return (1);
	init_data(&data);
	mlx_hook(data.win_3d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_2d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_3d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_2d, 17, 1L << 0, destroy_window, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}