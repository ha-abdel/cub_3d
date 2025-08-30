#include "cube_bonus.h"

int	handle_key(int key, t_data *data)
{
	double	old_px;
	double	old_py;

	old_px = data->player.x;
	old_py = data->player.y;
	if (key == ESC_KEY || key == 111)
	{
		if (key == 111)
			get_the_closest_door(data);
		else
			destroy_window(data);
	}
	move_player(data, key);
	check_collision(data, old_px, old_py);
	return (0);
}

int	handle_mouse(int x, int y, t_data *data)
{
	static int	oldx;

	(void)y;
	if (x < oldx)
		data->player.angle -= data->rotation_speed;
	else if (x > oldx)
		data->player.angle += data->rotation_speed;
	if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	oldx = x;
	return (0);
}