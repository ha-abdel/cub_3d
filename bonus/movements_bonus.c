#include "cube_bonus.h"
#include <stdbool.h>

bool is_valid_move(t_data *data, double x, double y)
{
	double safety = 6;
	
	if (is_wall(data, x, y) 
		|| (is_door(data, x, y) && (data->doors[get_door_index(data, construct_point(x, y))]->open == 0))
		|| (is_exit(data, x , y) && data->exit.open == 0))
			return (false);
	if (is_wall(data, x + safety, y) 
		|| (is_door(data, x + safety, y) && (data->doors[get_door_index(data, construct_point(x + safety, y))]->open == 0))
		|| (is_exit(data, x + safety , y) && data->exit.open == 0))
			return (false);
	if (is_wall(data, x - safety, y) 
		|| (is_door(data, x - safety, y) && (data->doors[get_door_index(data, construct_point(x - safety, y))]->open == 0))
		|| (is_exit(data, x - safety , y) && data->exit.open == 0))
			return (false);
	if (is_wall(data, x, y + safety) 
		|| (is_door(data, x, y + safety) && (data->doors[get_door_index(data, construct_point(x, y + safety))]->open == 0))
		|| (is_exit(data, x , y + safety) && data->exit.open == 0))
			return (false);
	if (is_wall(data, x, y - safety) 
		|| (is_door(data, x, y - safety) && (data->doors[get_door_index(data, construct_point(x, y - safety))]->open == 0))
		|| (is_exit(data, x , y - safety) && data->exit.open == 0))
			return (false);
	return true;
}

void	check_collision(t_data *data, double old_px, double old_py)
{
	if (!is_valid_move(data, data->player.x, data->player.y))
	{
		data->player.x = old_px;
		data->player.y = old_py;
	}
}

void	set_direction(t_data *data, int key)
{
	if (key == W_KEY)
	{
		data->event = UP;
		// data->player.x += cos(data->player.angle) * PLAYER_SPEED;
		// data->player.y += sin(data->player.angle) * PLAYER_SPEED;
	}
	if (key == S_KEY)
	{
		data->event = DOWN;
		// data->player.x += cos(data->player.angle + M_PI) * PLAYER_SPEED;
		// data->player.y += sin(data->player.angle + M_PI) * PLAYER_SPEED;
	}
	if (key == A_KEY)
	{
		data->event = LEFT;
		// data->player.x += cos(data->player.angle - M_PI_2) * PLAYER_SPEED;
		// data->player.y += sin(data->player.angle - M_PI_2) * PLAYER_SPEED;
	}
	if (key == D_KEY)
	{
		data->event = RIGHT;
		// data->player.x += cos(data->player.angle + M_PI_2) * PLAYER_SPEED;
		// data->player.y += sin(data->player.angle + M_PI_2) * PLAYER_SPEED;
	}
}

void	move_player(t_data *data)
{
	if (data->event == UP)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle);
		data->player.y += PLAYER_SPEED * sin(data->player.angle);
	}
	else if (data->event == DOWN)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle + M_PI);
		data->player.y += PLAYER_SPEED * sin(data->player.angle + M_PI);
	}
	if (data->event == LEFT)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle - M_PI_2);
		data->player.y += PLAYER_SPEED * sin(data->player.angle - M_PI_2);
	}
	if (data->event == RIGHT)
	{
		data->player.x += PLAYER_SPEED * cos(data->player.angle + M_PI_2);
		data->player.y += PLAYER_SPEED * sin(data->player.angle + M_PI_2);
	}
}
