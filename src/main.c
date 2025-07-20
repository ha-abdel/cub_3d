#include "../cube.h"

void    clean_mlx_mandatory_resources(t_data **data)
{
    if((*data)->E_wall.img)
        mlx_destroy_image((*data)->mlx, (*data)->E_wall.img);
    if((*data)->N_wall.img)
        mlx_destroy_image((*data)->mlx, (*data)->N_wall.img);
    if((*data)->S_wall.img)
        mlx_destroy_image((*data)->mlx, (*data)->S_wall.img);
    if((*data)->W_wall.img)
        mlx_destroy_image((*data)->mlx, (*data)->W_wall.img);
    if((*data)->bg.img)
        mlx_destroy_image((*data)->mlx, (*data)->bg.img);
    if((*data)->bg1.img)
        mlx_destroy_image((*data)->mlx, (*data)->bg1.img);
    if ((*data)->win_3d)
        mlx_destroy_window((*data)->mlx, (*data)->win_3d);
    if ((*data)->win_2d)
        mlx_destroy_window((*data)->mlx, (*data)->win_2d);
    if ((*data)->mlx)
        mlx_destroy_display((*data)->mlx);
    // free((*data)->mlx);

}

int    clean_all(t_data **data)
{
    clean_mlx_mandatory_resources(data);
    free((*data)->mlx);
    ft_malloc(0,0);
    exit(1);
    return 0;
}

int destroy_window(t_data *data)
{
    clean_all(&data);
    return 0;
}

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
}

void    rotate_player(t_data *data, int key)
{
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
}

int handle_key(int key, t_data *data)
{
    double old_px = data->player.x;
    double old_py = data->player.y;

    if (key == ESC_KEY)
        destroy_window(data);
    move_player(data, key);
    if (is_wall(data, data->player.x - is_facing_left(data->player.angle), data->player.y - is_facing_up(data->player.angle)))
    {
        data->player.x = old_px;
        data->player.y = old_py;
    }
    rotate_player(data, key);
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
    printf("\t x     : %0.2f\n",data->player.x / TILE_SIZE);
        printf("\t y     : %0.2f\n",data->player.y / TILE_SIZE);
        printf("-----------------------------------------\n");
}



int main(int ac, char **av) {
    t_data data;

    if (ac != 2)
        return 1;
    initial_data(&data);
    if (!main_function_parsing(&data, av[1]))
        return (1);
    init_data(&data);

    // ft_player_debug(&data);

    mlx_hook(data.win_3d, 2, 1L<<0, handle_key, &data);
    mlx_hook(data.win_2d, 2, 1L<<0, handle_key, &data);
    mlx_hook(data.win_3d, 17, 1L<<0, destroy_window, &data);
    mlx_hook(data.win_2d, 17, 1L<<0, destroy_window, &data);
   
    // mlx_hook(data.win_2d, 6, 1L<<6, handle_mouse, &data);
    // mlx_hook(data.win_3d, 6, 1L<<6, handle_mouse, &data);
    
    mlx_loop_hook(data.mlx, render, &data);
    mlx_loop(data.mlx);
    return 0;
}