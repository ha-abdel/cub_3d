/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/04 14:56:30 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

long	get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

void	player_won(t_data *data)
{
	int		y;
	int		x;

	y = (int)((data->player.y / TILE_SIZE) - TILE_SIZE / 2);
	x = (int)((data->player.x / TILE_SIZE) - TILE_SIZE / 2);
	if (x < 0 || y < 0)
		return ;
	if (data->map.map[y][x] == 'P')
	{
		printf("YOU WON\n");
		destroy_window(data);
	}
}

void	animate_exit(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < 16)
	{
		x = data->exit.frame_exit.frame_count;
		while (x < (data->exit.frame_exit.frame_count + 16))
		{
			color = get_color(&data->exit_sprite, x, y);
			if (color != 0x00000000)
				my_mlx_pixel_put(&data->exit.frame_exit, x
					- data->exit.frame_exit.frame_count, y, color);
			x++;
		}
		y++;
	}
	if (data->exit.frame_exit.frame_count < 512)
		data->exit.frame_exit.frame_count += 16;
	else
		data->exit.frame_exit.frame_count = 0;
}

int	render(t_data *data)
{
	// static long	start_time;
	//long	current_time;

	// start_time = get_time();

	//current_time = get_time();
	//if ((current_time - data->start_time) >= (1000 / 30))
	//{
		//data->start_time = current_time;
		// printf("hello\n");
			clear_image(&data->bg1, BLACK);
			animate_door(data);
			animate_exit(data);
			player_won(data);
			draw_direction_lines(data);
			draw_map(data);
			cast_rays(data);
			create_minimap(data);
			mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
			mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
			//mlx_mouse_move(data->mlx, data->win_3d, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//}
	// else
	// {
	// 		// printf("%ld\n", (current_time - start_time));
	// 	return 0;
	// }
	
	// static int	frame_counter;

	// if (frame_counter >= 60)
	// {
		
		// frame_counter = 0;
	// }
	// frame_counter++;
	return (0);
}
// int	render(t_data *data)
// {
// 	static int	frame_counter;

// 	if (frame_counter >= 60)
// 	{
// 		clear_image(&data->bg1, BLACK);
// 		animate_door(data);
// 		draw_direction_lines(data);
// 		draw_map(data);
// 		cast_rays(data);
// 		create_minimap(data);
// 		mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
// 		mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
// 		mlx_mouse_move(data->mlx, data->win_3d, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
// 		frame_counter = 0;
// 	}
// 	frame_counter++;
// 	return (0);
// }
