#include "cube_bonus.h"

void	check_collision(t_data *data, int old_px, int old_py)
{
	if (is_wall(data, data->player.x - is_facing_left(data->player.angle),
			data->player.y - is_facing_up(data->player.angle)))
	{
		data->player.x = old_px;
		data->player.y = old_py;
	}
	if (is_door(data, data->player.x - is_facing_left(data->player.angle), data->player.y - is_facing_up(data->player.angle))
		&& (data->doors[get_door_index(data, construct_point(data->player.x
					- is_facing_left(data->player.angle), data->player.y
					- is_facing_up(data->player.angle)))]->open == 0))
	{
		data->player.x = old_px;
		data->player.y = old_py;
	}
}

void	move_player(t_data *data, int key)
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