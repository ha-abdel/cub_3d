#include "cube.h"

void    init_data(t_data *data)
{
    data->mlx = mlx_init();
    data->win_3d = mlx_new_window(data->mlx, screen_width, screen_height, "3D View");
    data->win_2d = mlx_new_window(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE, "2D Debug View");

    data->bg.img = mlx_new_image(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE);
    data->bg.addr = mlx_get_data_addr(data->bg.img, &data->bg.bpp, &data->bg.line_len, &data->bg.endian);
    data->bg.width = data->map.width * TILE_SIZE;
    data->bg.height = data->map.height * TILE_SIZE;
    data->bg1.img = mlx_new_image(data->mlx, screen_width, screen_height);
    data->bg1.addr = mlx_get_data_addr(data->bg1.img, &data->bg1.bpp, &data->bg1.line_len, &data->bg1.endian);
    data->bg1.width = screen_width;
    data->bg1.height = screen_height;
    data->player.x *= TILE_SIZE + TILE_SIZE/2;
    data->player.y *= TILE_SIZE + TILE_SIZE/2;
    // data->player.angle = 45;

}

void    initial_data(t_data *data)
{
    data->map.c_color = -1;
    data->map.f_color = -1;
    data->map.direction = 0;
    data->map.height = 0;
    data->map.width = 0;
    data->map.map = NULL;
    data->player.angle = -1;
    data->map.n_path = NULL;
    data->map.s_path = NULL;
    data->map.w_path = NULL;
    data->map.e_path = NULL;
    data->player.y = -1;
    data->player.x = -1;
    data->NUM_RAYS = screen_width;
}

void    init_ray(t_ray *ray, t_data *data)
{
    ray->ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    ray->angle_step = (FOV * PI / 180.0) / data->NUM_RAYS;
    ray->distance = 0;
    ray->player.x = data->player.x;
    ray->player.y = data->player.y;
}