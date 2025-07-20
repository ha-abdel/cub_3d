#include "cube_bonus.h"

void cast_rays(t_data *data)
{
    t_ray   ray;
    t_door  door;
    int     i;
    
    i = 0;
    ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    door.ray.ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    while (i < data->num_rays)
    {
        init_ray(&ray, data, &door);
        ray.wall_type = NONE;
        check_horizontal_intersect(data, &ray, &door);
        check_vertical_intersect(data, &ray, &door);
        calc_distance(data, &ray, &door);
        wall_projection(data, &ray, i, &door);
        ray.ray_angle += ray.angle_step;
        door.ray.ray_angle = ray.ray_angle;
        i++;
    }
}


