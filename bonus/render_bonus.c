/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 13:37:14 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

long	get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	render(t_data *data)
{
	long	current_time;
	// int x,y;

	current_time = get_time();
	if ((current_time - data->start_time) >= (1000 / 30))
	{
		data->start_time = current_time;
		// printf("hello\n");
			clear_image(&data->bg1, BLACK);
			animate_door(data);
			animate_exit(data);
			//player_won(data);
			// draw_direction_lines(data);
			// draw_map(data);
			cast_rays(data);
			create_minimap(data);
			// mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
			mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
			mlx_mouse_move(data->mlx, data->win_3d, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else
	{
			// printf("%ld\n", (current_time - start_time));
		return 0;
	}
	
	// static int	frame_counter;

	// if (frame_counter >= 60)
	// {
		
		// frame_counter = 0;
	// }
	// frame_counter++;
	return (0);
}
