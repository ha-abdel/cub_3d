/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:17 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/03 19:14:07 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


int	count_doors(t_data **data)
{
	int y;
	int	x;
	int count;

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
	(*data)->doors[index]->frame_door.img = mlx_new_image((*data)->mlx, 32, 32);
	(*data)->doors[index]->frame_door.addr = mlx_get_data_addr((*data)->doors[index]->frame_door.img,
			&(*data)->doors[index]->frame_door.bpp, &(*data)->doors[index]->frame_door.line_len,
			&(*data)->doors[index]->frame_door.endian);
	(*data)->doors[index]->frame_door.height = 32;
	(*data)->doors[index]->frame_door.width = 32;
	(*data)->doors[index]->frame_door.frame_count = 0;
	init_ray(&(*data)->doors[index]->ray, *data);
}

void	save_doors_info(t_data **data)
{
	int y;
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
	data->win_2d = mlx_new_window(data->mlx, data->map.width * TILE_SIZE,
			data->map.height * TILE_SIZE, "2D Debug View");
	init_images(&data);
	data->bg.width = data->map.width * TILE_SIZE;
	data->bg.height = data->map.height * TILE_SIZE;
	data->bg1.width = SCREEN_WIDTH;
	data->bg1.height = SCREEN_HEIGHT;
	ft_bzero(&data->mini_map, sizeof(t_minimap));
	data->player.x = (data->player.x * TILE_SIZE) + TILE_SIZE / 2;
    data->player.y = (data->player.y * TILE_SIZE) + TILE_SIZE / 2;
	data->exit.open = 0;
	data->nb_doors = count_doors(&data);
	save_doors_info(&data);
}

void	initial_data(t_data *data)
{
	data->map.c_color = -1;
	data->map.f_color = -1;
	data->map.direction = 0;
	data->map.height = 0;
	data->map.width = 0;
	data->map.map = NULL;
	data->player.angle = -1;
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
}

void	init_ray(t_ray *ray, t_data *data)
{
	ray->h_intersect.x = 0;
	ray->h_intersect.y = 0;
	ray->v_intersect.x = 0;
	ray->v_intersect.y = 0;
	ray->angle_step = (FOV * PI / 180.0) / data->num_rays;
	ray->player.x = data->player.x;
	ray->player.y = data->player.y;
	ray->wall_type = NONE;
}
