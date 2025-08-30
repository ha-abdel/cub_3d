/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:27 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/08/30 15:54:07 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"









// void	get_the_closest_door(t_data *data)
// {
// 	int	i;
// 	int	index;
// 	int	dt;
// 	int	dx;
// 	int	dy;
// 	int	dist;

// 	index = -1;
// 	dt = INT_MAX;
// 	i = 0;
// 	while (data->doors[i])
// 	{
// 		dx = abs(data->doors[i]->col * TILE_SIZE - (int)(data->player.x));
// 		dy = abs(data->doors[i]->row * TILE_SIZE - (int)(data->player.y));
// 		dist = dx + dy;
// 		// Check if closer and inside FOV
// 		if (dist < dt && check_zone(data, data->doors[i]))
// 		{
// 			dt = dist;
// 			index = i;
// 			// printf("closest door is %d\n", index);
// 		}
// 		i++;
// 	}
// 	if (index != -1 && check_distance(data))
// 		data->doors[index]->open = 1;
// }




int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	initial_data(&data);
	if (!main_function_parsing(&data, av[1]))
		return (1);
	init_data(&data);
	// print_data(&data);
	fill_img_door(&data);
	// print_info(&data);
	mlx_hook(data.win_3d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_2d, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.win_3d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_2d, 17, 1L << 0, destroy_window, &data);
	mlx_hook(data.win_2d, 6, 1L << 6, handle_mouse, &data);
	mlx_hook(data.win_3d, 6, 1L << 6, handle_mouse, &data);
	mlx_mouse_hide(data.mlx, data.win_3d);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
