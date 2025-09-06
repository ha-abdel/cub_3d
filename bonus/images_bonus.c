/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:34:40 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 14:16:18 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	check_addresses(t_data **data)
{
	if (!(*data)->bg1.img || !(*data)->n_wall.img || !(*data)->s_wall.img
		|| !(*data)->e_wall.img || !(*data)->w_wall.img || !(*data)->door.img
		|| !(*data)->exit_sprite.img || !(*data)->exit_sprite.img
		|| !(*data)->exit.frame_exit.img || !(*data)->minimap.img)
		clean_all(data);
}

void	get_imgs_addresses(t_data **data)
{
	check_addresses(data);
	(*data)->bg1.addr = mlx_get_data_addr((*data)->bg1.img, &(*data)->bg1.bpp,
			&(*data)->bg1.line_len, &(*data)->bg1.endian);
	(*data)->n_wall.addr = mlx_get_data_addr((*data)->n_wall.img,
			&(*data)->n_wall.bpp, &(*data)->n_wall.line_len,
			&(*data)->n_wall.endian);
	(*data)->s_wall.addr = mlx_get_data_addr((*data)->s_wall.img,
			&(*data)->s_wall.bpp, &(*data)->s_wall.line_len,
			&(*data)->s_wall.endian);
	(*data)->e_wall.addr = mlx_get_data_addr((*data)->e_wall.img,
			&(*data)->e_wall.bpp, &(*data)->e_wall.line_len,
			&(*data)->e_wall.endian);
	(*data)->w_wall.addr = mlx_get_data_addr((*data)->w_wall.img,
			&(*data)->w_wall.bpp, &(*data)->w_wall.line_len,
			&(*data)->w_wall.endian);
	(*data)->door.addr = mlx_get_data_addr((*data)->door.img,
			&(*data)->door.bpp, &(*data)->door.line_len, &(*data)->door.endian);
	(*data)->exit_sprite.addr = mlx_get_data_addr((*data)->exit_sprite.img,
			&(*data)->exit_sprite.bpp, &(*data)->exit_sprite.line_len,
			&(*data)->exit_sprite.endian);
	(*data)->minimap.addr = mlx_get_data_addr((*data)->minimap.img,
			&(*data)->minimap.bpp, &(*data)->minimap.line_len,
			&(*data)->minimap.endian);
	(*data)->exit.frame_exit.addr = mlx_get_data_addr((*data)->exit.frame_exit.img,
			&(*data)->exit.frame_exit.bpp, &(*data)->exit.frame_exit.line_len,
			&(*data)->exit.frame_exit.endian);
	(*data)->exit_sprite.addr = mlx_get_data_addr((*data)->exit_sprite.img,
			&(*data)->exit_sprite.bpp, &(*data)->exit_sprite.line_len,
			&(*data)->exit_sprite.endian);
}

void	init_images(t_data **data)
{
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
			"wolfenstein/door.xpm", &(*data)->door.width,
			&(*data)->door.height);
	(*data)->exit_sprite.img = mlx_xpm_file_to_image((*data)->mlx,
			"wolfenstein/grey_stone.xpm", &(*data)->exit_sprite.width,
			&(*data)->exit_sprite.height);
	(*data)->minimap.img = mlx_xpm_file_to_image((*data)->mlx, SAHM,
			&(*data)->minimap.width, &(*data)->minimap.height);
	(*data)->exit_sprite.img = mlx_xpm_file_to_image((*data)->mlx,
			"wolfenstein/exit_1_.xpm", &(*data)->exit_sprite.width,
			&(*data)->exit_sprite.height);
	(*data)->exit.frame_exit.img = mlx_new_image((*data)->mlx, 16, 16);
	get_imgs_addresses(data);
}
