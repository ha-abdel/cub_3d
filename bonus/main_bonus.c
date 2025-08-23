/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:27 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/23 15:44:13 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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

int	check_zone(t_data *data, t_door *door)
{
	double	door_cx;
	double	door_cy;
	double	dx;
	double	dy;
	double	angle_to_door;
	double	diff;

	door_cx = door->col * TILE_SIZE + TILE_SIZE / 2;
	door_cy = door->row * TILE_SIZE + TILE_SIZE / 2;
	dx = door_cx - data->player.x;
	dy = door_cy - data->player.y;
	angle_to_door = atan2(dy, dx);
	diff = angle_to_door - data->player.angle;
	if (diff > M_PI)
		diff -= 2 * M_PI;
	else if (diff < -M_PI)
		diff += 2 * M_PI;
	return (fabs(diff) <= FOV / 2);
}

int	check_distance(t_data *data)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)data->player.x / TILE_SIZE;
	tile_y = (int)data->player.y / TILE_SIZE;
	if (data->map.width > tile_x + 2 && is_facing_right(data->player.angle)
		&& (data->map.map[tile_y][tile_x + 2] == 'D'
			|| data->map.map[tile_y][tile_x + 1] == 'D'))
		return (1);
	else if (data->map.height > tile_y + 2 && is_facing_down(data->player.angle)
		&& (data->map.map[tile_y + 2][tile_x] == 'D' || data->map.map[tile_y
			+ 1][tile_x] == 'D'))
		return (1);
	else if (tile_x - 2 >= 0 && is_facing_left(data->player.angle)
		&& (data->map.map[tile_y][tile_x - 2] == 'D'
			|| data->map.map[tile_y][tile_x - 1] == 'D'))
		return (1);
	else if (tile_y - 2 >= 0 && is_facing_up(data->player.angle)
		&& (data->map.map[tile_y - 2][tile_x] == 'D' || data->map.map[tile_y
			- 1][tile_x] == 'D'))
		return (1);
	return (0);
}

void	get_the_closest_door(t_data *data)
{
	int	i;
	int	index;
	int	dt;
	int	dx;
	int	dy;
	int	dist;

	index = -1;
	dt = INT_MAX;
	i = 0;
	while (data->doors[i])
	{
		dx = abs(data->doors[i]->col * TILE_SIZE - (int)(data->player.x));
		dy = abs(data->doors[i]->row * TILE_SIZE - (int)(data->player.y));
		dist = dx + dy;
		// Check if closer and inside FOV
		if (dist < dt && check_zone(data, data->doors[i]))
		{
			dt = dist;
			index = i;
			printf("closest door is %d\n", index);
		}
		i++;
	}
	if (index != -1 && check_distance(data))
		data->doors[index]->open = 1;
}

int	handle_key(int key, t_data *data)
{
	double	old_px;
	double	old_py;

	old_px = data->player.x;
	old_py = data->player.y;
	if (key == ESC_KEY || key == 111)
	{
		if (key == 111)
			get_the_closest_door(data);
		else
			destroy_window(data);
		print_info(data);
	}
	move_player(data, key);
	if (is_wall(data, data->player.x - is_facing_left(data->player.angle),
			data->player.y - is_facing_up(data->player.angle)))
	{
		// printf("is wall\n");
		data->player.x = old_px;
		data->player.y = old_py;
	}
	if (is_door(data, data->player.x - is_facing_left(data->player.angle), data->player.y - is_facing_up(data->player.angle))
		&& (data->doors[get_door_index(data, construct_point(data->player.x
					- is_facing_left(data->player.angle), data->player.y
					- is_facing_up(data->player.angle)))]->open = 1))
	{
		// printf("is door\n");
		data->player.x = old_px;
		data->player.y = old_py;
	}
	return (0);
}

void	print_info(t_data *data)
{
	int	i;

	i = 0;
	while (data->doors[i])
	{
		printf("door id is %d\n", i + 1);
		printf("door col is %d\n", data->doors[i]->col);
		printf("door row is %d\n", data->doors[i]->row);
		printf("door is open %s\n", data->doors[i]->open ? "true" : "false");
		i++;
	}
}

void	print_hit_info(t_data *data)
{
	printf("door hit horizontally %d\n", data->hit.is_h_door);
	printf("door hit vertically %d\n", data->hit.is_v_door);
	printf("wall hit horizontally %d\n", data->hit.is_h_wall);
	printf("wall hit vertically %d\n", data->hit.is_v_wall);
	printf("final hit door %d\n", data->hit.is_door);
	printf("final hit wall %d\n", data->hit.is_wall);
	printf("h dist %f\n", data->hit.h_dist);
	printf("v dist %f\n", data->hit.v_dist);
}

void	fill_img_door(t_data *data)
{
	int				x;
	int				y;
	int				i;
	unsigned int	color;

	i = 0;
	while (data->doors[i])
	{
		y = 0;
		while (y < 32)
		{
			x = 0;
			while (x < 32)
			{
				color = get_color(&data->door, x, y);
				if (color != 0x00000000)
					my_mlx_pixel_put(&data->doors[i]->frame_door, x, y, color);
				x++;
			}
			y++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	initial_data(&data);
	if (!main_function_parsing(&data, av[1]))
		return (1);
	init_data(&data);
	print_data(&data);
	fill_img_door(&data);
	// print_info(&data);
	mlx_hook(data.win_3d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_2d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_3d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_2d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_2d, 6, 1L << 6, handle_mouse, &data);
	mlx_hook(data.win_3d, 6, 1L << 6, handle_mouse, &data);
	mlx_mouse_hide(data.mlx, data.win_3d);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
