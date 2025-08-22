/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:17 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/22 19:01:06 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	init_images(t_data **data)
{
	(*data)->bg.img = mlx_new_image((*data)->mlx, (*data)->map.width
			* TILE_SIZE, (*data)->map.height * TILE_SIZE);
	(*data)->bg1.img = mlx_new_image((*data)->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	(*data)->n_wall.img = mlx_xpm_file_to_image((*data)->mlx,
			(*data)->map.n_path, &(*data)->n_wall.width,
			&(*data)->n_wall.height);
	(*data)->s_wall.img = mlx_xpm_file_to_image((*data)->mlx,
			(*data)->map.s_path, &(*data)->s_wall.width,
			&(*data)->s_wall.height);
	(*data)->e_wall.img = mlx_xpm_file_to_image((*data)->mlx,
			(*data)->map.e_path, &(*data)->e_wall.width,
			&(*data)->e_wall.height);
	(*data)->w_wall.img = mlx_xpm_file_to_image((*data)->mlx,
			(*data)->map.w_path, &(*data)->w_wall.width,
			&(*data)->w_wall.height);
	(*data)->door.img = mlx_xpm_file_to_image((*data)->mlx,
			"wolfenstein/bab.xpm", &(*data)->door.width,
			&(*data)->door.height);
	(*data)->minimap.img = mlx_xpm_file_to_image((*data)->mlx, SAHM,
			&(*data)->minimap.width, &(*data)->minimap.height);
	// (*data)->frame_door.img = mlx_new_image((*data)->mlx, 250, 250);
	get_imgs_addresses(data);
}

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
	// if (index == 0)
	// 	(*data)->doors[index]->open = 1;
	// else
		(*data)->doors[index]->open = 0;
	(*data)->doors[index]->frame_door.img = mlx_new_image((*data)->mlx, 100, 100);
	(*data)->doors[index]->frame_door.addr = mlx_get_data_addr((*data)->doors[index]->frame_door.img,
			&(*data)->doors[index]->frame_door.bpp, &(*data)->doors[index]->frame_door.line_len,
			&(*data)->doors[index]->frame_door.endian);
	(*data)->doors[index]->frame_door.height = 100;
	(*data)->doors[index]->frame_door.width = 100;
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
	(*data)->doors = ft_malloc((count_doors(data) + 1) * sizeof(t_door), 1);
	if (!(*data)->doors)
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
	// data->num_rays = SCREEN_WIDTH;
	data->win_3d = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"3D View");
	data->win_2d = mlx_new_window(data->mlx, data->map.width * TILE_SIZE,
			data->map.height * TILE_SIZE, "2D Debug View");
	init_images(&data);
	data->bg.width = data->map.width * TILE_SIZE;
	data->bg.height = data->map.height * TILE_SIZE;
	data->bg1.width = SCREEN_WIDTH;
	data->bg1.height = SCREEN_HEIGHT;
	// data->frame_door.width = 250;
	// data->frame_door.height = 250;
	// data->frame_door.frame_count = 0;
	ft_bzero(&data->mini_map, sizeof(t_minimap));
	data->player.x = (data->player.x * TILE_SIZE) + TILE_SIZE / 2;
    data->player.y = (data->player.y * TILE_SIZE) + TILE_SIZE / 2;
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
