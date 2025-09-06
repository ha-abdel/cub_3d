/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:24:37 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/09/06 15:25:09 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	print_info(t_data *data)
{
	int	i;

	i = 0;
	while (data->doors[i])
	{
		printf("door id is %d\n", i + 1);
		printf("door col is %d\n", data->doors[i]->col);
		printf("door row is %d\n", data->doors[i]->row);
		i++;
	}
}

void	print_hit_info(t_data *data)
{
	printf("door hit horizontally %d\n", data->hit.is_h_door);
	printf("door hit vertically %d\n", data->hit.is_v_door);
	printf("wall hit horizontally %d\n", data->hit.is_h_wall);
	printf("wall hit vertically %d\n", data->hit.is_v_wall);
	printf("final hit door %d\n", data->hit.is_door);
	printf("final hit wall %d\n", data->hit.is_wall);
	printf("h dist %f\n", data->hit.h_dist);
	printf("v dist %f\n", data->hit.v_dist);
}
