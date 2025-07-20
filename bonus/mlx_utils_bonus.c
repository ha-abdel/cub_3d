#include "cube_bonus.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	is_door(t_data *data, double x, double y)
{
	int		grid_x;
	int		grid_y;
	char	c;

	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= data->map.height
		|| grid_x >= data->map.width)
		return (0);
	c = data->map.map[grid_y][grid_x];
	if (c == 'D')
		return (1);
	return (0);
}

int	is_wall(t_data *data, double x, double y)
{
	int		grid_x;
	int		grid_y;
	char	c;

	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= data->map.height
		|| grid_x >= data->map.width)
		return (0);
	c = data->map.map[grid_y][grid_x];
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

int	inside_bounds(t_data *data, double x, double y)
{
	(void)data;
	if (x < 0 || x >= screen_width || y < 0 || y >= screen_height)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(t_sprite *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len) + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

void	clear_image(t_sprite *img, int color)
{
	int y = 0;
	int x;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}