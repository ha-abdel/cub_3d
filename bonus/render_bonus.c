/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/23 11:06:39 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

// int	render(t_data *data)
// {
// 	static int	frame_counter;

// 	if (frame_counter >= 600)
// 	{
// 		clear_image(&data->bg1, BLACK);
// 		animate_door(data);
// 		draw_map(data);
// 		cast_rays(data);
// 		draw_direction_lines(data);
// 		create_minimap(data);
// 		mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
// 		mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
// 		frame_counter = 0;
// 	}
// 	frame_counter++;
// 	return (0);
// }

t_door  *check_zone(t_data *data)
{
    int     i;
    int     index;
    int     dx;
    int     dy;
    int     dt;

    i = 0;
    dx = abs(data->door[i]->x - (int)(data->player.x / TILE_SIZE));
    dy = abs(data->door[i]->y - (int)(data->player.y / TILE_SIZE));
    dt = dx + dy;
    index = 0;
    i++;
    while (data->door[i])
    {
        dx = abs(data->door[i]->x - (int)(data->player.x / TILE_SIZE));
        dy = abs(data->door[i]->y - (int)(data->player.y / TILE_SIZE));
        if (dt > (dx + dy))
        {
            dt = dx + dy;
            index = i;
        }
        else if (dt == (dx + dy))
        {
            if (index > i)
                index = i;
        }
        i++;
    }
    return (data->door[index]);
}


int	render(t_data *data)
{
    static int frame_counter;
    static  int door;
    
    // Use a smaller frame counter to improve performance
    // if (frame_counter >= 600)  // Reduced from 600 for better performance
    // {
    //     clear_image(&data->bg1, BLACK);
    //     if (data->open_door && !data->rev_animation)
    //         make_door_open(data);
    //     if (check_if_player_pass(data) && data->frame_door.frame_count >= 660 && !data->rev_animation)
    //     {
    //         //printf("here\n");
    //         data->frame_door.frame_count = 0;
    //         data->rev_animation = 1;
    //     }
    //     if (data->rev_animation && check_if_player_pass(data))
    //     {
    //         if (data->frame_door.reverse_frame > 0)
    //         {
    //             animate_reverse_door(data);
    //         }
    //         if (data->frame > 700 && data->frame_door.reverse_frame > 0)
	//         {
    //             data->frame_door.reverse_frame -= 165;
	// 	        data->frame = 0;
	//         }
    //         if (!data->frame_door.reverse_frame)
    //         {
    //             data->rev_animation = 0;
    //             data->open_door = 0;
    //         }
    //     }
    //     if (!door)
    //     {
    //         animate_door(data);
    //         door = 1;
    //     }
	clear_image(&data->bg1, BLACK);
        draw_map(data);
        // check_zone(data);
        cast_rays(data);
        draw_direction_lines(data);
        create_minimap(data);
        
        mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
        mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
        
        frame_counter = 0;
    // }
    // frame_counter++;
    // data->frame++;
    return 0;
}