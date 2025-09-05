#include "cube_bonus.h"

int	handle_key(int key, t_data *data)
{
	if (key == ESC_KEY)
		data->event.quit = true;
	if (key == O_KEY)
		data->event.open_door = true;
	if (key == W_KEY)
		data->event.up = true;
	if (key == S_KEY)
		data->event.down = true;
	if (key == D_KEY)
		data->event.right = true;
	if (key == A_KEY)
		data->event.left = true;
	return (0);
}
int	release_key(int key, t_data *data)
{
	if (key == ESC_KEY)
		data->event.quit = false;
	if (key == O_KEY)
		data->event.open_door = false;
	if (key == W_KEY)
		data->event.up = false;
	if (key == S_KEY)
		data->event.down = false;
	if (key == D_KEY)
		data->event.right = false;
	if (key == A_KEY)
		data->event.left = false;
	return (0);
}

// int	handle_mouse(int x, int y, t_data *data)
// {
// 	data->event = MOUSE_MOVE;
// 	data->mouse.x = x;
// 	data->mouse.y = y;
// 	// static int	oldx;

// 	// (void)y;
// 	// if (x < oldx)
// 	// 	data->player.angle -= data->rotation_speed;
// 	// else if (x > oldx)
// 	// 	data->player.angle += data->rotation_speed;
// 	// if (data->player.angle > 2 * PI)
// 	// 	data->player.angle -= 2 * PI;
// 	// if (data->player.angle < 0)
// 	// 	data->player.angle += 2 * PI;
// 	// oldx = x;
// 	return (0);
// }
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