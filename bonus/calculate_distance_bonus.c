#include "cube_bonus.h"

void    calc_wall_distance(t_data *data, t_ray **ray, t_door **door)
{
    (void)door;
    (*ray)->h_dist = ((*ray)->h_intersect.x - data->player.x) * ((*ray)->h_intersect.x - data->player.x) + ((*ray)->h_intersect.y - data->player.y) * ((*ray)->h_intersect.y - data->player.y);
    (*ray)->v_dist = ((*ray)->v_intersect.x - data->player.x) * ((*ray)->v_intersect.x - data->player.x) + ((*ray)->v_intersect.y - data->player.y) * ((*ray)->v_intersect.y - data->player.y);

    if ((*ray)->h_dist < (*ray)->v_dist)
    {
        (*ray)->distance = sqrt((*ray)->h_dist);
        (*ray)->ray_end.x = (*ray)->h_intersect.x;
        (*ray)->ray_end.y = (*ray)->h_intersect.y;
    } else 
    {
        (*ray)->distance = sqrt((*ray)->v_dist);
        (*ray)->ray_end.x = (*ray)->v_intersect.x;
        (*ray)->ray_end.y = (*ray)->v_intersect.y;
    }
    (*ray)->distance *= cos((*ray)->ray_angle - data->player.angle);
}
void    calc_door_distance(t_data *data, t_ray **ray, t_door **door)
{
    (void)ray;
    (*door)->ray.h_dist = ((*door)->ray.h_intersect.x - data->player.x) * ((*door)->ray.h_intersect.x - data->player.x) + ((*door)->ray.h_intersect.y - data->player.y) * ((*door)->ray.h_intersect.y - data->player.y);
    (*door)->ray.v_dist = ((*door)->ray.v_intersect.x - data->player.x) * ((*door)->ray.v_intersect.x - data->player.x) + ((*door)->ray.v_intersect.y - data->player.y) * ((*door)->ray.v_intersect.y - data->player.y);

    if ((*door)->ray.h_dist < (*door)->ray.v_dist)
    {
        (*door)->ray.distance = sqrt((*door)->ray.h_dist);
        (*door)->ray.ray_end.x = (*door)->ray.h_intersect.x;
        (*door)->ray.ray_end.y = (*door)->ray.h_intersect.y;
    } else 
    {
        (*door)->ray.distance = sqrt((*door)->ray.v_dist);
        (*door)->ray.ray_end.x = (*door)->ray.v_intersect.x;
        (*door)->ray.ray_end.y = (*door)->ray.v_intersect.y;
    }
    (*door)->ray.distance *= cos((*door)->ray.ray_angle - data->player.angle);
}

void    calc_distance(t_data *data, t_ray *ray, t_door *door)
{
    calc_wall_distance(data, &ray, &door);
    if (door->found_door)
        calc_door_distance(data, &ray, &door);
    // else
    //     door->ray = *ray;
    // ray->h_dist = (ray->h_intersect.x - data->player.x) * (ray->h_intersect.x - data->player.x) + (ray->h_intersect.y - data->player.y) * (ray->h_intersect.y - data->player.y);
    // ray->v_dist = (ray->v_intersect.x - data->player.x) * (ray->v_intersect.x - data->player.x) + (ray->v_intersect.y - data->player.y) * (ray->v_intersect.y - data->player.y);

    // if (ray->h_dist < ray->v_dist)
    // {
    //     ray->distance = sqrt(ray->h_dist);
    //     ray->ray_end.x = ray->h_intersect.x;
    //     ray->ray_end.y = ray->h_intersect.y;
    // } else 
    // {
    //     ray->distance = sqrt(ray->v_dist);
    //     ray->ray_end.x = ray->v_intersect.x;
    //     ray->ray_end.y = ray->v_intersect.y;
    // }
    // ray->distance *= cos(ray->ray_angle - data->player.angle);
    draw_line(data, ray->player, ray->ray_end, BLUE, 2);
    if (door->found_door)
    {
        printf("wall distance is %0.2f ", ray->distance);
        printf("door distance is %0.2f \n", door->ray.distance);
        draw_line(data, door->ray.player, door->ray.ray_end, YELLOW, 2);
    }
}

// void calc_distance(t_data *data, t_ray *ray, t_door *door) {
//     // Calculate wall distances
//     ray->h_dist = (ray->h_intersect.x == 0 && ray->h_intersect.y == 0) ? INT_MAX :
//                  sqrt(pow(ray->h_intersect.x - data->player.x, 2) + 
//                       pow(ray->h_intersect.y - data->player.y, 2));
    
//     ray->v_dist = (ray->v_intersect.x == 0 && ray->v_intersect.y == 0) ? INT_MAX :
//                  sqrt(pow(ray->v_intersect.x - data->player.x, 2) + 
//                       pow(ray->v_intersect.y - data->player.y, 2));

//     ray->distance = fmin(ray->h_dist, ray->v_dist);

//     // Calculate door distances if door exists
//     if (door->is_door) {
//         door->ray.h_dist = sqrt(pow(door->ray.h_intersect.x - data->player.x, 2) + 
//                           pow(door->ray.h_intersect.y - data->player.y, 2));
//         door->ray.v_dist = sqrt(pow(door->ray.v_intersect.x - data->player.x, 2) + 
//                           pow(door->ray.v_intersect.y - data->player.y, 2));
//         door->ray.distance = fmin(door->ray.h_dist, door->ray.v_dist);
        
//         // The wall behind the door should use the original ray's distance
//         door->wall_behind_distance = ray->distance;
//     }
// }