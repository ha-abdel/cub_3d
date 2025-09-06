/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:04:24 by salahian          #+#    #+#             */
/*   Updated: 2025/09/06 11:12:11 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	make_animation(t_data *data, t_door *door)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < 64)
	{
		x = door->frame_door.frame_count;
		while (x < (door->frame_door.frame_count + 64))
		{
			color = get_color(&data->door, x, y);
			if (color != 0x00000000)
				my_mlx_pixel_put(&door->frame_door, x
					- door->frame_door.frame_count, y, color);
			x++;
		}
		y++;
	}
	if (door->frame_door.frame_count < 576)
		door->frame_door.frame_count += 64;
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
