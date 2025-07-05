#include "cube.h"

void    move_player(t_data *data, int key)
{
    if (key == W_KEY)
    {
        data->player.x += cos(data->player.angle) * PLAYER_SPEED;
        data->player.y += sin(data->player.angle) * PLAYER_SPEED;
    }
    if (key == S_KEY)
    {
        data->player.x += cos(data->player.angle + M_PI) * PLAYER_SPEED;
        data->player.y += sin(data->player.angle + M_PI) * PLAYER_SPEED;
    }
    if (key == A_KEY)
    {
        data->player.x += cos(data->player.angle - M_PI_2) * PLAYER_SPEED;
        data->player.y += sin(data->player.angle - M_PI_2) * PLAYER_SPEED;
    }
    if (key == D_KEY)
    {
        data->player.x += cos(data->player.angle + M_PI_2) * PLAYER_SPEED;
        data->player.y += sin(data->player.angle + M_PI_2) * PLAYER_SPEED;
    }
    // if (key == W_KEY)
    // {
    //     data->player.x += cos(data->player.angle) * PLAYER_SPEED;
    //     data->player.y += sin(data->player.angle) * PLAYER_SPEED;
    // }
    // if (key == S_KEY)
    // {
    //     data->player.x -= cos(data->player.angle) * PLAYER_SPEED;
    //     data->player.y -= sin(data->player.angle) * PLAYER_SPEED;
    // }
    // if (key == A_KEY)
    // {
    //     data->player.x += sin(data->player.angle) * PLAYER_SPEED;
    //     data->player.y -= cos(data->player.angle) * PLAYER_SPEED;
    // }
    // if (key == D_KEY)
    // {
    //     data->player.x -= sin(data->player.angle) * PLAYER_SPEED;
    //     data->player.y += cos(data->player.angle) * PLAYER_SPEED;
    // }
    // if (is_wall(data, data->player.x - is_facing_left(data->player.angle), data->player.y - is_facing_up(data->player.angle)))
    // {
    //     data->player.x = old_px;
    //     data->player.y = old_py;
    // }
}

int handle_key(int key, t_data *data)
{
    double old_px = data->player.x;
    double old_py = data->player.y;

    if (key == ESC_KEY) {
        mlx_destroy_window(data->mlx, data->win_3d);
        mlx_destroy_window(data->mlx, data->win_2d);
        exit(0);
    }
    move_player(data, key);
    if (is_wall(data, data->player.x - is_facing_left(data->player.angle), data->player.y - is_facing_up(data->player.angle)))
    {
        data->player.x = old_px;
        data->player.y = old_py;
    }
    if (key == LEFT_ARROW)
	{
	 	data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}	
    if (key == RIGHT_ARROW)
    {
		data->player.angle += ROTATION_SPEED;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}  
    return 0;
}


int    render(t_data *data)
{
    static int frame_counter;
    if (frame_counter == 60)
    {
        clear_image(&data->bg1, BLACK);

        draw_map(data);
        cast_rays(data);
        draw_direction_lines(data);
        mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
        mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
      
        frame_counter = 0;
        // getchar();
    }
    frame_counter++;
    // usleep(2000);
    return 0;
}
void ft_player_debug(t_data * data)
{
    printf("\t angle : %0.2f\n",data->player.angle * 180 / PI);
    printf("\t x     : %0.2f\n",data->player.x);
        printf("\t y     : %0.2f\n",data->player.y);
        printf("-----------------------------------------\n");
}
int main(int ac, char **av) {
    t_data data;

    if (ac != 2)
        return 1;
    initial_data(&data);
    main_function_parsing(&data, av[1]);
    init_data(&data);

    mlx_hook(data.win_3d, 2, 1L<<0, handle_key, &data);
    mlx_hook(data.win_2d, 2, 1L<<0, handle_key, &data);
    
   mlx_loop_hook(data.mlx, render, &data);
    mlx_loop(data.mlx);
    return 0;
}