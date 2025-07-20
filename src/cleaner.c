/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:02 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 17:27:03 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	clean_mlx_mandatory_resources(t_data **data)
{
	if ((*data)->e_wall.img)
		mlx_destroy_image((*data)->mlx, (*data)->e_wall.img);
	if ((*data)->n_wall.img)
		mlx_destroy_image((*data)->mlx, (*data)->n_wall.img);
	if ((*data)->s_wall.img)
		mlx_destroy_image((*data)->mlx, (*data)->s_wall.img);
	if ((*data)->w_wall.img)
		mlx_destroy_image((*data)->mlx, (*data)->w_wall.img);
	if ((*data)->bg.img)
		mlx_destroy_image((*data)->mlx, (*data)->bg.img);
	if ((*data)->bg1.img)
		mlx_destroy_image((*data)->mlx, (*data)->bg1.img);
	if ((*data)->win_3d)
		mlx_destroy_window((*data)->mlx, (*data)->win_3d);
	if ((*data)->win_2d)
		mlx_destroy_window((*data)->mlx, (*data)->win_2d);
	if ((*data)->mlx)
		mlx_destroy_display((*data)->mlx);
}

int	clean_all(t_data **data)
{
	clean_mlx_mandatory_resources(data);
	free((*data)->mlx);
	ft_malloc(0, 0);
	exit(1);
	return (0);
}

int	destroy_window(t_data *data)
{
	clean_all(&data);
	return (0);
}
