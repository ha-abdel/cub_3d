/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 18:04:53 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

// t_door  *check_zone(t_data *data)
// {
//     int     i;
//     int     index;
//     int     dx;
//     int     dy;
//     int     dt;

//     i = 0;
//     if (!data->door || !data->door[0])
//         return (NULL);
//     dx = abs(data->door[i]->x - (int)(data->player.x / TILE_SIZE));
//     dy = abs(data->door[i]->y - (int)(data->player.y / TILE_SIZE));
//     dt = dx + dy;
//     index = 0;
//     i++;
//     while (data->door[i])
//     {
//         dx = abs(data->door[i]->x - (int)(data->player.x / TILE_SIZE));
//         dy = abs(data->door[i]->y - (int)(data->player.y / TILE_SIZE));
//         if (dt > (dx + dy))
//         {
//             dt = dx + dy;
//             index = i;
//         }
//         else if (dt == (dx + dy))
//         {
//             if (index > i)
//                 index = i;
//         }
//         i++;
//     }
//     return (data->door[index]);
// }
// int	render(t_data *data)
// {
//     static int frame_counter;
    
//     if (frame_counter >= 600)
//     {
//         clear_image(&data->bg1, BLACK);
//         draw_map(data);
//         handle_animation_door(data, get_the_closest_door(data));
//         cast_rays(data);
//         draw_direction_lines(data);
//         create_minimap(data);
//         mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
//         mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
//         frame_counter = 0;
//     }
//     frame_counter++;
//     data->frame++;
//     return 0;
// }
