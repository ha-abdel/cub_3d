/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/20 11:05:29 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	render(t_data *data)
{
	static int	frame_counter;

	if (frame_counter >= 600)
	{
		clear_image(&data->bg1, BLACK);
		fill_img_door(data);
		animate_door(data);
		draw_direction_lines(data);
		draw_map(data);
		cast_rays(data);
		create_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
		mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
		frame_counter = 0;
	}
	frame_counter++;
	return (0);
}
