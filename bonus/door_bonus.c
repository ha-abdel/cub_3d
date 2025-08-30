#include "cube_bonus.h"

void	fill_img_door(t_data *data)
{
	int				x;
	int				y;
	int				i;
	unsigned int	color;

	i = 0;
	while (data->doors[i])
	{
		y = 0;
		while (y < 32)
		{
			x = 0;
			while (x < 32)
			{
				color = get_color(&data->door, x, y);
				if (color != 0x00000000)
					my_mlx_pixel_put(&data->doors[i]->frame_door, x, y, color);
				x++;
			}
			y++;
		}
		i++;
	}
}
int	check_zone(t_data *data, t_door *door)
{
	double	door_cx;
	double	door_cy;
	double	dx;
	double	dy;
	double	angle_to_door;
	double	diff;

	door_cx = door->col * TILE_SIZE + TILE_SIZE / 2;
	door_cy = door->row * TILE_SIZE + TILE_SIZE / 2;
	dx = door_cx - data->player.x;
	dy = door_cy - data->player.y;
	angle_to_door = atan2(dy, dx);
	diff = angle_to_door - data->player.angle;
	if (diff > M_PI)
		diff -= 2 * M_PI;
	else if (diff < -M_PI)
		diff += 2 * M_PI;
	return (fabs(diff) <= FOV / 2);
}

int	check_distance(t_data *data)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)data->player.x / TILE_SIZE;
	tile_y = (int)data->player.y / TILE_SIZE;
	if (data->map.width > tile_x + 2 && is_facing_right(data->player.angle)
		&& (data->map.map[tile_y][tile_x + 2] == 'D'
			|| data->map.map[tile_y][tile_x + 1] == 'D'))
		return (1);
	else if (data->map.height > tile_y + 2 && is_facing_down(data->player.angle)
		&& (data->map.map[tile_y + 2][tile_x] == 'D' || data->map.map[tile_y
			+ 1][tile_x] == 'D'))
		return (1);
	else if (tile_x - 2 >= 0 && is_facing_left(data->player.angle)
		&& (data->map.map[tile_y][tile_x - 2] == 'D'
			|| data->map.map[tile_y][tile_x - 1] == 'D'))
		return (1);
	else if (tile_y - 2 >= 0 && is_facing_up(data->player.angle)
		&& (data->map.map[tile_y - 2][tile_x] == 'D' || data->map.map[tile_y
			- 1][tile_x] == 'D'))
		return (1);
	return (0);
}

void	get_the_closest_door(t_data *data)
{
	int i;
	int index;
	int dx;
	int dy;
	int dt;

	index = -1;
	i = 0;
	dt = INT_MAX;
	while (i < data->nb_doors)
	{
		if (data->front_doors[i] == 1 && data->doors[i]->open == 0)
		{
			dx = abs(data->doors[i]->col * TILE_SIZE - (int)(data->player.x));
			dy = abs(data->doors[i]->row * TILE_SIZE - (int)(data->player.y));
			if (dx + dy <= dt)
			{
				dt = dx + dy;
				index = i;
			}
		}
		i++;
	}
	if (index != -1 && check_distance(data))
		data->doors[index]->open = 1;
}


int	get_door_index(t_data *data, t_point p)
{
	int	i;

	i = 0;
	while (data && data->doors && data->doors[i])
	{
		if (data->doors[i]->col  == (int)(p.x / TILE_SIZE) && 
			data->doors[i]->row  == (int)(p.y / TILE_SIZE))
				return i;
		i++;
	}
	return (-1);
	
}