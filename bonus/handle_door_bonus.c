/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 08:58:03 by salahian          #+#    #+#             */
/*   Updated: 2025/07/23 18:17:38 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void    init_door_img(t_data *data, int i)
{
    data->door[i]->frame_door.img = mlx_new_image(data->mlx, 165, 150);
    data->door[i]->frame_door.height = 150;
    data->door[i]->frame_door.width = 165;
    data->door[i]->frame_count = 0;
	data->door[i]->reverse_frame = 660;
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
        init_door_img(data, i);
        set_info(data, &data->door[i]);
        i++;
    }
    data->door[i] = NULL;
}

void    main_func_doors(t_data *data)
{
    int     count;

    count = calculate_doors(data);
    printf("[%d]\n", count);
    data->door = ft_malloc(sizeof(t_door *) * (count + 1), 1);
    fill_door(data, count);
}