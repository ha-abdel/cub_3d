/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/08 09:05:01 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	rotate_view(t_data *data)
{
	if (data->mouse.x > (SCREEN_WIDTH / 2))
	{
		data->player.angle += data->rotation_speed;
	}
	else
	{
		data->player.angle -= data->rotation_speed;
	}
}

void	check_movements(t_data *data)
{
	double	old_px;
	double	old_py;

	old_px = data->player.x;
	old_py = data->player.y;
	move_player(data);
	check_collision(data, old_px, old_py);
}

void	check_other_events(t_data *data)
{
	if (data->event.open_door == true)
		get_the_closest_door(data);
	else if (data->event.quit == true)
		destroy_window(data);
}

int	render(t_data *data)
{
	long	current_time;
	int		x;
	int		y;

	current_time = get_time();
	if ((current_time - data->start_time) >= (1000 / 30))
	{
		data->start_time = current_time;
		check_movements(data);
		check_other_events(data);
		animate_door(data);
		animate_exit(data);
		cast_rays(data);
		create_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
		mlx_mouse_move(data->mlx, data->win_3d, SCREEN_WIDTH / 2, SCREEN_HEIGHT
			/ 2);
		mlx_mouse_get_pos(data->mlx, data->win_3d, &x, &y);
	}
	return (0);
}
