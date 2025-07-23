#include "cube_bonus.h"

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

int handle_mouse(int x, int y, t_data *data)
{
    (void)y;
    static int oldx;
    // double offset;

    // offset = x - oldx;
    if (x < oldx)
        data->player.angle -= ROTATION_SPEED;
    else if (x > oldx)
        data->player.angle += ROTATION_SPEED;

    // printf("mouse is moved %d\n", x);
    if (data->player.angle > 2 * PI)
	    data->player.angle -= 2 * PI;
    if (data->player.angle < 0)
		data->player.angle += 2 * PI;
    oldx = x;
    return 0;
}

// int     check_distance(t_data *data)
// {
//     if (data->map.width >= (((int)data->player.x / TILE_SIZE) + 2) && is_facing_right(data->player.angle) && (data->map.map[((int)data->player.y / TILE_SIZE)][((int)data->player.x / TILE_SIZE) + 2] == 'D'))
//         return (1);
//     else if (data->map.height >= (((int)data->player.y / TILE_SIZE) + 2) && is_facing_down(data->player.angle) && (data->map.map[((int)data->player.y / TILE_SIZE) + 2][(int)data->player.x / TILE_SIZE] == 'D'))
//         return (1);
//     else if (((((int)data->player.x / TILE_SIZE) - 2) > 0) && is_facing_left(data->player.angle) && (data->map.map[((int)data->player.y / TILE_SIZE)][((int)data->player.x / TILE_SIZE) - 2] == 'D'))
//         return (1);
//     else if (((((int)data->player.y / TILE_SIZE) - 2) > 0) && is_facing_up(data->player.angle) && (data->map.map[((int)data->player.y / TILE_SIZE) - 2][(int)data->player.x / TILE_SIZE] == 'D'))
//         return (1);
//     return (0);
// }
int check_distance(t_data *data)
{
    int tile_x = (int)data->player.x / TILE_SIZE;
    int tile_y = (int)data->player.y / TILE_SIZE;

    if (data->map.width > tile_x + 2
        && is_facing_right(data->player.angle)
        && (data->map.map[tile_y][tile_x + 2] == 'D' || data->map.map[tile_y][tile_x + 1] == 'D'))
        return (1);
    else if (data->map.height > tile_y + 2
        && is_facing_down(data->player.angle)
        && (data->map.map[tile_y + 2][tile_x] == 'D' || data->map.map[tile_y + 1][tile_x] == 'D'))
        return (1);
    else if (tile_x - 2 >= 0
        && is_facing_left(data->player.angle)
        && (data->map.map[tile_y][tile_x - 2] == 'D' || data->map.map[tile_y][tile_x - 1] == 'D'))
        return (1);
    else if (tile_y - 2 >= 0
        && is_facing_up(data->player.angle)
        && (data->map.map[tile_y - 2][tile_x] == 'D' || data->map.map[tile_y - 1][tile_x] == 'D'))
        return (1);
    return (0);
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
    if (key == 111)
        data->open_door = check_distance(data);
    move_player(data, key);
    if (is_wall(data, data->player.x - is_facing_left(data->player.angle), data->player.y - is_facing_up(data->player.angle))
        || is_door(data, data->player.x - is_facing_left(data->player.angle), data->player.y - is_facing_up(data->player.angle)) && 
        data->open_door == 0)
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

void    make_door_open(t_data *data)
{

    if (data->frame_door.frame_count < 660)
        animate_door(data);
    if (data->frame > 700)
	{
		data->frame_door.frame_count += 165;
		data->frame = 0;
	}
    data->frame_door.reverse_frame = 660;
    data->rev_animation = 0;
    // else if (!check_distance(data) && data->frame_door.frame_count >= 660)
    // {
    //     if (data->frame_door.frame_count > 0)
    //         animate_reverse_door(data);
    //     if (data->frame > 350)
	//     {
	// 	    data->frame_door.frame_count -= 165;
	// 	    data->frame = 0;
	//     }
    //     data->open_door = 0;
    // }
}

int check_if_player_pass(t_data *data)
{
    int tile_x = (int)data->player.x / TILE_SIZE;
    int tile_y = (int)data->player.y / TILE_SIZE;

    if (data->map.map[tile_y][tile_x] != 'D')
        return (1);
    return (0);
}

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

int render(t_data *data)
{
    static int frame_counter;
    static  int door;
    
    // Use a smaller frame counter to improve performance
    if (frame_counter >= 60)  // Reduced from 600 for better performance
    {
        clear_image(&data->bg1, BLACK);
        if (data->open_door && !data->rev_animation)
            make_door_open(data);
        if (check_if_player_pass(data) && data->frame_door.frame_count >= 660 && !data->rev_animation)
        {
            //printf("here\n");
            data->frame_door.frame_count = 0;
            data->rev_animation = 1;
        }
        if (data->rev_animation && check_if_player_pass(data))
        {
            if (data->frame_door.reverse_frame > 0)
            {
                animate_reverse_door(data);
            }
            if (data->frame > 700 && data->frame_door.reverse_frame > 0)
	        {
                data->frame_door.reverse_frame -= 165;
		        data->frame = 0;
	        }
            if (!data->frame_door.reverse_frame)
            {
                data->rev_animation = 0;
                data->open_door = 0;
            }
        }
        if (!door)
        {
            animate_door(data);
            door = 1;
        }
        draw_map(data);
        check_zone(data);
        cast_rays(data);
        draw_direction_lines(data);
        create_minimap(data);
        
        mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
        mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
        
        frame_counter = 0;
    }
    frame_counter++;
    data->frame++;
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
    mlx_hook(data.win_2d, 6, 1L<<6, handle_mouse, &data);
    mlx_hook(data.win_3d, 6, 1L<<6, handle_mouse, &data);
    mlx_mouse_hide(data.mlx,data.win_3d);
    
    mlx_loop_hook(data.mlx, render, &data);
    mlx_loop(data.mlx);
    return 0;
}