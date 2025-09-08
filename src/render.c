/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 17:46:38 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_collision(t_data *data, double old_px, double old_py)
{
	if (!is_valid_move(data, data->player.x, data->player.y))
	{
		data->player.x = old_px;
		data->player.y = old_py;
	}
}

int	render(t_data *data)
{
	static int	frame_counter;

	if (frame_counter == 60)
	{
		cast_rays(data);
		mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
		frame_counter = 0;
	}
	frame_counter++;
	return (0);
}
