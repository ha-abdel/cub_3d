#include "cube.h"

void    wall_projection(t_data *data, t_ray *ray, int *color, int col)
{
    ray->dist_projection_plane = (screen_width / 2.0) / tan ((FOV / 2.0) * PI / 180);
    ray->wall_strip = (TILE_SIZE / ray->distance) * ray->dist_projection_plane;
    ray->ceil = (screen_height) / 2 - ray->wall_strip / 2;
    ray->floor = ray->ceil + ray->wall_strip;
    if (ray->ceil < 0)
        ray->ceil = 0;
    if (ray->floor > screen_height)
        ray->floor = screen_height;
    ray->wall_start.x = col;
    ray->wall_start.y = ray->ceil;
    ray->wall_end.x = col;
    ray->wall_end.y = ray->floor;
    
    ray->ceil_start.x = col;
    ray->ceil_start.y = 0;
    ray->ceil_end.x = col;
    ray->ceil_end.y = ray->ceil - 1;

    ray->floor_start.x = col;
    ray->floor_start.y = ray->ceil + ray->wall_strip;
    ray->floor_end.x = col;
    ray->floor_end.y = screen_height;
    draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
    draw_line(data, ray->wall_start, ray->wall_end, *color, 1);
    draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
}