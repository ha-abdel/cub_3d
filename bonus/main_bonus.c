/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:27 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/05 15:56:55 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"


int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	initial_data(&data);
	if (!main_function_parsing(&data, av[1]))
		return (1);
	init_data(&data);
	fill_img_door(&data);
	mlx_hook(data.win_3d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_2d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_3d, 3, 1L << 1, release_key, &data);
	mlx_hook(data.win_2d, 3, 1L << 1, release_key, &data);
	mlx_hook(data.win_3d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_2d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_2d, 6, 1L << 6, handle_mouse, &data);
	mlx_hook(data.win_3d, 6, 1L << 6, handle_mouse, &data);
	mlx_mouse_hide(data.mlx, data.win_3d);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
