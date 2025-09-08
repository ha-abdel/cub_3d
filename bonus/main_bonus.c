/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:27 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/08 18:01:33 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	check_addresses(t_data **data)
{
	if (!(*data)->bg1.img || !(*data)->door.img || !(*data)->exit_sprite.img
		|| !(*data)->exit_sprite.img || !(*data)->exit.frame_exit.img
		|| !(*data)->minimap.img)
		clean_all(data);
}

void	check_walls_addresses(t_data **data)
{
	if (!(*data)->n_wall.img || !(*data)->s_wall.img || !(*data)->e_wall.img
		|| !(*data)->w_wall.img)
		clean_all(data);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	initial_data(&data);
	if (!main_function_parsing(&data, av[1]))
	{
		ft_malloc(0, 0);
		return (1);
	}
	init_data(&data);
	fill_img_door(&data);
	mlx_hook(data.win_3d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_3d, 3, 1L << 1, release_key, &data);
	mlx_hook(data.win_3d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_3d, 6, 1L << 6, handle_mouse, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
