#include "cube_bonus.h"

void	init_data(t_data *data)
{
	int	a;
	int	b;

    a = 0;
    b = 0;
    data->mlx = mlx_init();
    data->NUM_RAYS = screen_width; // Set number of rays to match screen width
    
    // Create windows with correct dimensions
    data->win_3d = mlx_new_window(data->mlx, screen_width, screen_height, "3D View");
    data->win_2d = mlx_new_window(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE, "2D Debug View");

    // Create image for 3D view with correct dimensions
    data->bg1.img = mlx_new_image(data->mlx, screen_width, screen_height);
    data->bg1.addr = mlx_get_data_addr(data->bg1.img, &data->bg1.bpp, &data->bg1.line_len, &data->bg1.endian);
    data->bg1.width = screen_width;
    data->bg1.height = screen_height;
    
    // Create image for 2D view
    data->bg.img = mlx_new_image(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE);
    data->bg.addr = mlx_get_data_addr(data->bg.img, &data->bg.bpp, &data->bg.line_len, &data->bg.endian);
    data->bg.width = data->map.width * TILE_SIZE;
    data->bg.height = data->map.height * TILE_SIZE;
    
    // Load textures
    data->N_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.n_path, &data->N_wall.width, &data->N_wall.height);
    data->N_wall.addr = mlx_get_data_addr(data->N_wall.img, &data->N_wall.bpp, &data->N_wall.line_len, &data->N_wall.endian);
    // data->N_wall.width =  TILE_SIZE;
    // data->N_wall.height = TILE_SIZE;

    data->S_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.s_path, &data->S_wall.width, &data->S_wall.height);
    data->S_wall.addr = mlx_get_data_addr(data->S_wall.img, &data->S_wall.bpp, &data->S_wall.line_len, &data->S_wall.endian);
    // data->S_wall.width =  TILE_SIZE;
    // data->S_wall.height = TILE_SIZE;

    data->E_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.e_path, &data->E_wall.width, &data->E_wall.height);
    data->E_wall.addr = mlx_get_data_addr(data->E_wall.img, &data->E_wall.bpp, &data->E_wall.line_len, &data->E_wall.endian);
    // data->E_wall.width =  TILE_SIZE;
    // data->E_wall.height = TILE_SIZE;

    data->W_wall.img = mlx_xpm_file_to_image(data->mlx, data->map.w_path, &data->W_wall.width, &data->W_wall.height);
    data->W_wall.addr = mlx_get_data_addr(data->W_wall.img, &data->W_wall.bpp, &data->W_wall.line_len, &data->W_wall.endian);

    data->door.img = mlx_xpm_file_to_image(data->mlx, "wolfenstein/animated_door.xpm", &data->door.width, &data->door.height);
    data->door.addr = mlx_get_data_addr(data->door.img, &data->door.bpp, &data->door.line_len, &data->door.endian);
    // data->W_wall.width =  TILE_SIZE;
    // data->W_wall.height = TILE_SIZE;
    data->minimap.img = mlx_xpm_file_to_image(data->mlx, SAHM, &a, &b);
    data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bpp, &data->minimap.line_len, &data->minimap.endian);
    data->frame_door.img = mlx_new_image(data->mlx, 250, 250);
    data->frame_door.addr = mlx_get_data_addr(data->frame_door.img, &data->frame_door.bpp, &data->frame_door.line_len, &data->frame_door.endian);
    data->frame_door.frame_count = 0;
    data->minimap.width = a;
    data->minimap.height = b;
    ft_bzero(&data->mini_map, sizeof(t_minimap));
    data->player.x *= TILE_SIZE + TILE_SIZE/2;
    data->player.y *= TILE_SIZE + TILE_SIZE/2;

    // data->player.angle = 45;

}

void	initial_data(t_data *data)
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

void	init_ray(t_ray *ray, t_data *data, t_door *door)
{
	ray->h_intersect.x = 0;
	ray->h_intersect.y = 0;
	ray->v_intersect.x = 0;
	ray->v_intersect.y = 0;
	ray->angle_step = (FOV * PI / 180.0) / data->NUM_RAYS;
	ray->distance = 0;
	ray->player.x = data->player.x;
	ray->player.y = data->player.y;
	door->found_door = 0;
	door->found_door_pixel = 0;
	door->ray.angle_step = ray->angle_step;
	door->ray.distance = 0;
	door->ray.player.x = data->player.x;
	door->ray.player.y = data->player.y;
	door->ray.h_intersect.x = 0;
	door->ray.h_intersect.y = 0;
	door->ray.v_intersect.x = 0;
	door->ray.v_intersect.y = 0;
	door->wall_behind_distance = 0;
}
