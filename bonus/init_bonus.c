/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:17 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 10:55:32 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

// void	init_images(t_data **data)
// {
// 	(*data)->bg.img = mlx_new_image((*data)->mlx, (*data)->map.width
// 			* TILE_SIZE, (*data)->map.height * TILE_SIZE);
// 	(*data)->bg1.img = mlx_new_image((*data)->mlx, screen_width, screen_height);
// 	(*data)->n_wall.img = mlx_xpm_file_to_image((*data)->mlx,
// 			(*data)->map.n_path, &(*data)->n_wall.width,
// 			&(*data)->n_wall.height);
// 	(*data)->s_wall.img = mlx_xpm_file_to_image((*data)->mlx,
// 			(*data)->map.s_path, &(*data)->s_wall.width,
// 			&(*data)->s_wall.height);
// 	(*data)->e_wall.img = mlx_xpm_file_to_image((*data)->mlx,
// 			(*data)->map.e_path, &(*data)->e_wall.width,
// 			&(*data)->e_wall.height);
// 	(*data)->w_wall.img = mlx_xpm_file_to_image((*data)->mlx,
// 			(*data)->map.w_path, &(*data)->w_wall.width,
// 			&(*data)->w_wall.height);
// 	(*data)->door.img = mlx_xpm_file_to_image((*data)->mlx,
// 			"wolfenstein/animated_door.xpm", &(*data)->door.width,
// 			&(*data)->door.height);
// 	(*data)->minimap.img = mlx_xpm_file_to_image((*data)->mlx, SAHM,
// 			&(*data)->minimap.width, &(*data)->minimap.height);
// 	(*data)->frame_door.img = mlx_new_image((*data)->mlx, 250, 250);
// 	get_imgs_addresses(data);
// }

void	init_data(t_data *data)
{
	int	a;
	int	b;

    a = 0;
    b = 0;
    data->mlx = mlx_init();
    data->num_rays = screen_width; // Set number of rays to match screen width
    
    // Create windows with correct dimensions
    data->win_3d = mlx_new_window(data->mlx, screen_width, screen_height, "3D View");
    data->win_2d = mlx_new_window(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE, "2D Debug View");

    // Create image for 3D view with correct dimensions
    data->bg1.img = mlx_new_image(data->mlx, screen_width, screen_height);
    data->bg1.addr = mlx_get_data_addr(data->bg1.img, &data->bg1.bpp, &data->bg1.line_len, &data->bg1.endian);
    data->bg1.width = screen_width;
    data->bg1.height = screen_height;
    
    // Create image for 2D view
    data->bg.img = mlx_new_image(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE);
    data->bg.addr = mlx_get_data_addr(data->bg.img, &data->bg.bpp, &data->bg.line_len, &data->bg.endian);
    data->bg.width = data->map.width * TILE_SIZE;
    data->bg.height = data->map.height * TILE_SIZE;
    
    // Load textures
    data->n_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.n_path, &data->n_wall.width, &data->n_wall.height);
    data->n_wall.addr = mlx_get_data_addr(data->n_wall.img, &data->n_wall.bpp, &data->n_wall.line_len, &data->n_wall.endian);
    // data->n_wall.width =  TILE_SIZE;
    // data->n_wall.height = TILE_SIZE;

    data->s_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.s_path, &data->s_wall.width, &data->s_wall.height);
    data->s_wall.addr = mlx_get_data_addr(data->s_wall.img, &data->s_wall.bpp, &data->s_wall.line_len, &data->s_wall.endian);
    // data->s_wall.width =  TILE_SIZE;
    // data->s_wall.height = TILE_SIZE;

    data->e_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.e_path, &data->e_wall.width, &data->e_wall.height);
    data->e_wall.addr = mlx_get_data_addr(data->e_wall.img, &data->e_wall.bpp, &data->e_wall.line_len, &data->e_wall.endian);
    // data->e_wall.width =  TILE_SIZE;
    // data->e_wall.height = TILE_SIZE;

    data->w_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.w_path, &data->w_wall.width, &data->w_wall.height);
    data->w_wall.addr = mlx_get_data_addr(data->w_wall.img, &data->w_wall.bpp, &data->w_wall.line_len, &data->w_wall.endian);

    data->sprite_door.img = mlx_xpm_file_to_image(data->mlx, "wolfenstein/test7.xpm", &data->sprite_door.width, &data->sprite_door.height);
    data->sprite_door.addr = mlx_get_data_addr(data->sprite_door.img, &data->sprite_door.bpp, &data->sprite_door.line_len, &data->sprite_door.endian);
    // data->w_wall.width =  TILE_SIZE;
    // data->w_wall.height = TILE_SIZE;
    data->minimap.img = mlx_xpm_file_to_image(data->mlx, SAHM, &a, &b);
    data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bpp, &data->minimap.line_len, &data->minimap.endian);
    data->frame_door.img = mlx_new_image(data->mlx, 165, 150);
    data->frame_door.addr = mlx_get_data_addr(data->frame_door.img, &data->frame_door.bpp, &data->frame_door.line_len, &data->frame_door.endian);
    data->frame_door.height = 150;
    data->frame_door.width = 165;
    data->frame_door.frame_count = 0;
    data->rev_animation = 0;
	// data->frame_door.reverse_frame = 660;
    data->minimap.width = a;
    data->minimap.height = b;
	data->frame = 0;
    ft_bzero(&data->mini_map, sizeof(t_minimap));
    data->player.x *= TILE_SIZE + TILE_SIZE/2;
    data->player.y *= TILE_SIZE + TILE_SIZE/2;

    // data->player.angle = 45;

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
    data->num_rays = screen_width;
    // data->open_door = 0;
    data->rev_animation = 0;
}

void	init_ray(t_ray *ray, t_data *data, t_door *door)
{
	ray->h_intersect.x = 0;
	ray->h_intersect.y = 0;
	ray->v_intersect.x = 0;
	ray->v_intersect.y = 0;
	ray->angle_step = (FOV * PI / 180.0) / data->num_rays;
	ray->distance = 0;
	ray->player.x = data->player.x;
	ray->player.y = data->player.y;
	door->found_door = 0;
	door->found_door_pixel = 0;
	door->ray.angle_step = ray->angle_step;
	door->ray.distance = 0;
	door->ray.player.x = data->player.x;
	door->ray.player.y = data->player.y;
	door->ray.h_intersect.x = 0;
	door->ray.h_intersect.y = 0;
	door->ray.v_intersect.x = 0;
	door->ray.v_intersect.y = 0;
	door->wall_behind_distance = 0;
}
