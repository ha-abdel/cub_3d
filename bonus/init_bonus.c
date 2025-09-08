/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:17 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/08 14:13:54 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	count_doors(t_data **data)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (y < (*data)->map.height)
	{
		x = 0;
		while (x < (*data)->map.width)
		{
			if ((*data)->map.map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	fill_door(t_data **data, int index, t_point p)
{
	(*data)->doors[index] = ft_malloc(sizeof(t_door), 1);
	if (!(*data)->doors[index])
		destroy_window(*data);
	(*data)->doors[index]->col = p.x;
	(*data)->doors[index]->row = p.y;
	(*data)->doors[index]->open = 0;
	(*data)->doors[index]->frame_door.img = mlx_new_image((*data)->mlx, 64, 64);
	(*data)->doors[index]->frame_door.addr = mlx_get_data_addr((*data)->doors[index]->frame_door.img,
			&(*data)->doors[index]->frame_door.bpp,
			&(*data)->doors[index]->frame_door.line_len,
			&(*data)->doors[index]->frame_door.endian);
	(*data)->doors[index]->frame_door.height = 64;
	(*data)->doors[index]->frame_door.width = 64;
	(*data)->doors[index]->frame_door.frame_count = 0;
}

void	save_doors_info(t_data **data)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	(*data)->doors = ft_malloc(((*data)->nb_doors + 1) * sizeof(t_door), 1);
	(*data)->front_doors = ft_malloc((*data)->nb_doors * sizeof(int), 1);
	if (!(*data)->doors || !(*data)->front_doors)
		destroy_window(*data);
	while (y < (*data)->map.height)
	{
		x = 0;
		while (x < (*data)->map.width)
		{
			if ((*data)->map.map[y][x] == 'D')
			{
				fill_door(data, i, construct_point(x, y));
				i++;
			}
			x++;
		}
		y++;
	}
	(*data)->doors[i] = NULL;
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win_3d = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"3D View");
	init_wall_images(&data);
	init_images(&data);
	ft_bzero(&data->mini_map, sizeof(t_minimap));
	data->bg1.width = SCREEN_WIDTH;
	data->bg1.height = SCREEN_HEIGHT;
	data->player.x = (data->player.x * TILE_SIZE) + TILE_SIZE / 2;
	data->player.y = (data->player.y * TILE_SIZE) + TILE_SIZE / 2;
	data->nb_doors = count_doors(&data);
	data->exit.frame_exit.height = 16;
	data->exit.frame_exit.width = 16;
	data->exit.frame_exit.frame_count = 0;
	data->exit_sprite.frame_count = 0;
	data->center_mouse = true;
	data->event.space = false;
	save_doors_info(&data);
}

void	initial_data(t_data *data)
{
	data->map.c_color = -1;
	data->map.f_color = -1;
	data->map.direction = 0;
	data->map.height = 0;
	data->map.width = 0;
	data->player.angle = -1;
	data->map.map = NULL;
	data->map.n_path = NULL;
	data->map.s_path = NULL;
	data->map.w_path = NULL;
	data->map.e_path = NULL;
	data->player.y = -1;
	data->player.x = -1;
	data->num_rays = SCREEN_WIDTH;
	data->rotation_speed = M_PI / 180;
	data->max_dist_pixel = SCREEN_WIDTH * 2;
	data->start_time = get_time();
	data->mouse.old_x = SCREEN_WIDTH / 2;
	data->event.up = false;
	data->event.down = false;
	data->event.left = false;
	data->event.right = false;
	data->event.open_door = false;
	data->event.quit = false;
	data->event.mouse_move = false;
}
