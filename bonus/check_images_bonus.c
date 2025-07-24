/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_images_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:34:40 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/24 11:36:10 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	check_addresses(t_data **data)
{
	if (!(*data)->bg.img || !(*data)->bg1.img || !(*data)->n_wall.img
		|| !(*data)->s_wall.img || !(*data)->e_wall.img || !(*data)->w_wall.img
		|| !(*data)->sprite_door.img || !(*data)->minimap.img)
		clean_all(data);
}

void	get_imgs_addresses(t_data **data)
{
	check_addresses(data);
	(*data)->bg.addr = mlx_get_data_addr((*data)->bg.img, &(*data)->bg.bpp,
			&(*data)->bg.line_len, &(*data)->bg.endian);
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
	(*data)->sprite_door.addr = mlx_get_data_addr((*data)->sprite_door.img,
			&(*data)->sprite_door.bpp, &(*data)->sprite_door.line_len, &(*data)->sprite_door.endian);
	(*data)->minimap.addr = mlx_get_data_addr((*data)->minimap.img,
			&(*data)->minimap.bpp, &(*data)->minimap.line_len,
			&(*data)->minimap.endian);
	// (*data)->frame_door.addr = mlx_get_data_addr((*data)->frame_door.img,
	// 		&(*data)->frame_door.bpp, &(*data)->frame_door.line_len,
	// 		&(*data)->frame_door.endian);
}
