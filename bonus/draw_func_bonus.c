/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:14:00 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/24 16:47:34 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	draw_square(t_data *data, int x, int y, int color, int win)
{
	for (int dy = 0; dy < TILE_SIZE; dy++)
	{
		for (int dx = 0; dx < TILE_SIZE; dx++)
		{
			if (win == 1)
				my_mlx_pixel_put(&data->bg1, x + dx, y + dy, color);
			else
				my_mlx_pixel_put(&data->bg, x + dx, y + dy, color);
		}
	}
}

void	draw_line(t_data *data, t_point start_p, t_point end_p, int color,
		int win)
{
	t_point	point;
	double	dx;
	double	dy;
	double	steps;
	int		i;

	dx = end_p.x - start_p.x;
	dy = end_p.y - start_p.y;
	steps = fmax(fabs(dx), fabs(dy));
	steps = fmin(steps, data->max_dist_pixel);
	point.x = start_p.x;
	point.y = start_p.y;
	i = 0;
	while (i < steps)
	{
		if (win == 1)
			my_mlx_pixel_put(&data->bg1, (int)point.x, (int)point.y, color);
		else
			my_mlx_pixel_put(&data->bg, (int)point.x, (int)point.y, color);
		i++;
		point.x += dx / steps;
		point.y += dy / steps;
	}
}

void	draw_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			draw_square(data, x * TILE_SIZE, y * TILE_SIZE,
				data->map.map[y][x] == '1' ? BLACK : DARK_GRAY, 2);
			if (data->map.map[y][x] == 'D')
				draw_square(data, x * TILE_SIZE, y * TILE_SIZE, GREEN, 2);
			x++;
		}
		y++;
	}
}

void	draw_grid_lines(t_data *data)
{
	int		y;
	int		x;
	t_point	point1;
	t_point	point2;

	y = 0;
	x = 0;
	while (x < data->map.width)
	{
		point1.x = x * TILE_SIZE;
		point1.y = 0;
		point2.x = x * TILE_SIZE;
		point2.y = data->map.height * TILE_SIZE;
		draw_line(data, point1, point2, WHITE, 2);
		x++;
	}
	while (y < data->map.height)
	{
		point1.x = 0;
		point1.y = y * TILE_SIZE;
		point2.x = data->map.width * TILE_SIZE;
		point2.y = y * TILE_SIZE;
		draw_line(data, point1, point2, WHITE, 2);
		y++;
	}
}
void	draw_player(t_data *data)
{
	int	px;
	int	py;
	int	dy;
	int	dx;

	px = (int)data->player.x;
	py = (int)data->player.y;
	dy = -5;
	while (dy <= 5)
	{
		dx = -5;
		while (dx <= 5)
		{
			if (dx * dx + dy * dy <= 25)
				my_mlx_pixel_put(&data->bg, px + dx, py + dy, RED);
			dx++;
		}
		dy++;
	}
}
void	draw_direction_lines(t_data *data)
{
	t_point	point1;
	t_point	point2;
	int		px;
	int		py;
	int		dx;
	int		dy;

	px = (int)data->player.x;
	py = (int)data->player.y;
	dx = px + cos(data->player.angle) * 30;
	dy = py + sin(data->player.angle) * 30;
	point1.x = px;
	point1.y = py;
	point2.x = dx;
	point2.y = dy;
	draw_line(data, point1, point2, GREEN, 2);
}

void	draw_map(t_data *data)
{
	draw_walls(data);
	draw_grid_lines(data);
	draw_direction_lines(data);
	draw_player(data);
}
