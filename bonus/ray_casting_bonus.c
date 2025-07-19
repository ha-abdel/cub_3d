#include "cube_bonus.h"

void cast_rays(t_data *data)
{
    t_ray   ray;
    t_door  door;
    int     i;
    
    i = 0;
    init_ray(&ray, data, &door);

    // Make sure we're using screen_width for NUM_RAYS
    if (data->NUM_RAYS != screen_width)
        data->NUM_RAYS = screen_width;

    while (i < data->NUM_RAYS)
    {
        ray.wall_type = NONE;
        door.found_door = 0;
        door.found_door_pixel = 0;
        
        // Copy player position for each ray
        ray.player.x = data->player.x;
        ray.player.y = data->player.y;
        door.ray.player.x = data->player.x;
        door.ray.player.y = data->player.y;
        
        check_horizontal_intersect(data, &ray, &door);
        check_vertical_intersect(data, &ray, &door);
        calc_distance(data, &ray, &door);
        
        wall_projection(data, &ray, i, &door);
        
        ray.ray_angle += ray.angle_step;
        door.ray.ray_angle = ray.ray_angle;
        i++;
    }
}


