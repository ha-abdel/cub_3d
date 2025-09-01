/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/01 10:02:45 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	make_animation(t_data *data, t_door *door)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < 32)
	{
		x = door->frame_door.frame_count;
		while (x < (door->frame_door.frame_count + 32))
		{
			color = get_color(&data->door, x, y);
			if (color != 0x00000000)
				my_mlx_pixel_put(&door->frame_door, x
					- door->frame_door.frame_count, y, color);
			x++;
		}
		y++;
	}
	if (door->frame_door.frame_count < 480)
		door->frame_door.frame_count += 32;
	else
		door->open = 2;
}

void	animate_door(t_data *data)
{
	int	i;

	i = 0;
	while (data->doors[i])
	{
		if (data->doors[i]->open == 1)
		{
			make_animation(data, data->doors[i]);
			break ;
		}
		i++;
	}
}

int	render(t_data *data)
{
	static int	frame_counter;

	if (frame_counter >= 60)
	{
		clear_image(&data->bg1, BLACK);
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
