#include "../cube.h"

void cast_rays(t_data *data)
{
    t_ray   ray;
    int     i;
    int     color;
    
    i = 0;
    init_ray(&ray, data);

    while (i < data->NUM_RAYS)
    {
        ray.wall_type = NONE;
        check_horizontal_intersect(data, &ray);
        check_vertical_intersect(data, &ray);
        calc_distance(data, &ray, &color);
        wall_projection(data, &ray, &color, i);
        ray.ray_angle += ray.angle_step;
        i++;
    }
}


