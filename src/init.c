/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:32:21 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 15:47:46 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win_3d = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"3D View");
	data->win_2d = mlx_new_window(data->mlx, data->map.width * TILE_SIZE,
			data->map.height * TILE_SIZE, "2D Debug View");
	data->bg.img = mlx_new_image(data->mlx, data->map.width * TILE_SIZE,
			data->map.height * TILE_SIZE);
	data->bg.addr = mlx_get_data_addr(data->bg.img, &data->bg.bpp,
			&data->bg.line_len, &data->bg.endian);
	data->bg.width = data->map.width * TILE_SIZE;
	data->bg.height = data->map.height * TILE_SIZE;
	data->bg1.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->bg1.addr = mlx_get_data_addr(data->bg1.img, &data->bg1.bpp,
			&data->bg1.line_len, &data->bg1.endian);
	data->bg1.width = SCREEN_WIDTH;
	data->bg1.height = SCREEN_HEIGHT;
	data->n_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.n_path,
			&data->n_wall.width, &data->n_wall.height);
	data->n_wall.addr = mlx_get_data_addr(data->n_wall.img, &data->n_wall.bpp,
			&data->n_wall.line_len, &data->n_wall.endian);
	data->s_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.s_path,
			&data->s_wall.width, &data->s_wall.height);
	data->s_wall.addr = mlx_get_data_addr(data->s_wall.img, &data->s_wall.bpp,
			&data->s_wall.line_len, &data->s_wall.endian);
	data->e_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.e_path,
			&data->e_wall.width, &data->e_wall.height);
	data->e_wall.addr = mlx_get_data_addr(data->e_wall.img, &data->e_wall.bpp,
			&data->e_wall.line_len, &data->e_wall.endian);
	data->w_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.w_path,
			&data->w_wall.width, &data->w_wall.height);
	data->w_wall.addr = mlx_get_data_addr(data->w_wall.img, &data->w_wall.bpp,
			&data->w_wall.line_len, &data->w_wall.endian);
	data->player.x *= TILE_SIZE + TILE_SIZE / 2;
	data->player.y *= TILE_SIZE + TILE_SIZE / 2;
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
	ray->ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
	ray->angle_step = (FOV * PI / 180.0) / data->num_rays;
	ray->distance = 0;
	ray->player.x = data->player.x;
	ray->player.y = data->player.y;
}
