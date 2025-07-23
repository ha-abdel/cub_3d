/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:58:03 by salahian          #+#    #+#             */
/*   Updated: 2025/07/23 09:23:49 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void    init_door(t_data *data, int i)
{
    data->door[i]->frame_door.img = mlx_new_image(data->mlx, 165, 150);
    data->door[i]->frame_door.addr = mlx_get_data_addr(data->door[i]->frame_door.img, &data->door[i]->frame_door.bpp, &data->door[i]->frame_door.line_len, &data->door[i]->frame_door.endian);
    data->door[i]->frame_door.height = 150;
    data->door[i]->frame_door.width = 165;
    data->door[i]->frame_door.frame_count = 0;
	data->door[i]->frame_door.reverse_frame = 660;
}

int calculate_doors(t_data *data)
{
    int     count;
    int     i;
    int     j;

    i = 0;
    count = 0;
    while (data->map.map[i])
    {
        j = 0;
        while (data->map.map[i][j])
        {
            if (data->map.map[i][j] == 'D')
                count++;
            j++;
        }
        i++;
    }
    return (count);
}    

void    set_info(t_data *data, t_door **door)
{
    static int     i;
    static int     j;

    while (data->map.map[i])
    {
        if (j + 1 == data->map.width)
            j = 0;
        while (data->map.map[i][j])
        {
            if (data->map.map[i][j] == 'D')
            {
                (*door)->x = j;
                (*door)->y = i;
                return ;
            }
            j++;
        }
        i++;
    }
}

void    fill_door(t_data *data, int count)
{
    int     i;

    i = 0;
    while (i < count)
    {
        data->door[i] = ft_malloc(sizeof(t_door), 1);
        init_door(data, i);
        set_info(data, &data->door[i]);
        i++;
    }
    data->door[i] = NULL;
}

void    main_func_doors(t_data *data)
{
    int     count;

    count = calculate_doors(data);
    data->door = ft_malloc(sizeof(t_door *) * (count + 1), 1);
    fill_door(data, count);
}