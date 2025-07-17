#include "cube_bonus.h"

void cast_rays(t_data *data)
{
    t_ray   ray;
    t_door  door;
    int     i;
    
    i = 0;
    init_ray(&ray, data, &door);

    while (i < data->NUM_RAYS)
    {
        // init_ray(&door.ray, data, &door);
        ray.wall_type = NONE;
        check_horizontal_intersect(data, &ray, &door);
        check_vertical_intersect(data, &ray, &door);
        printf("%d\n", door.found_door);
        calc_distance(data, &ray, &door);
        wall_projection(data, &ray, i + 200, &door);
        ray.ray_angle += ray.angle_step;
        door.ray.ray_angle = ray.ray_angle;
        i++;
        door.found_door = 0;
        door.found_door_pixel = 0;
    }
}


