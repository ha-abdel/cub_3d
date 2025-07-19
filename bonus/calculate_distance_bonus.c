#include "cube_bonus.h"

void calc_wall_distance(t_data *data, t_ray **ray, t_door **door)
{
    (void)door;
    double h_dx = (*ray)->h_intersect.x - data->player.x;
    double h_dy = (*ray)->h_intersect.y - data->player.y;
    double v_dx = (*ray)->v_intersect.x - data->player.x;
    double v_dy = (*ray)->v_intersect.y - data->player.y;
    
    (*ray)->h_dist = h_dx * h_dx + h_dy * h_dy;
    (*ray)->v_dist = v_dx * v_dx + v_dy * v_dy;

    if ((*ray)->h_dist < (*ray)->v_dist)
    {
        (*ray)->distance = sqrt((*ray)->h_dist);
        (*ray)->ray_end.x = (*ray)->h_intersect.x;
        (*ray)->ray_end.y = (*ray)->h_intersect.y;
    }
    else 
    {
        (*ray)->distance = sqrt((*ray)->v_dist);
        (*ray)->ray_end.x = (*ray)->v_intersect.x;
        (*ray)->ray_end.y = (*ray)->v_intersect.y;
    }
    
    // Fix fisheye effect
    double angle_diff = (*ray)->ray_angle - data->player.angle;
    normalize_angle(&angle_diff);
    (*ray)->distance *= cos(angle_diff);
}

void calc_door_distance(t_data *data, t_ray **ray, t_door **door)
{
    (void)ray;
    if (!(*door)->found_door)
        return;
        
    double h_dx = 0, h_dy = 0, v_dx = 0, v_dy = 0;
    
    // Only calculate distance if we have valid coordinates
    if ((*door)->ray.h_intersect.x != 0 || (*door)->ray.h_intersect.y != 0)
    {
        h_dx = (*door)->ray.h_intersect.x - data->player.x;
        h_dy = (*door)->ray.h_intersect.y - data->player.y;
        (*door)->ray.h_dist = h_dx * h_dx + h_dy * h_dy;
    }
    else
    {
        (*door)->ray.h_dist = INFINITY;
    }
    
    if ((*door)->ray.v_intersect.x != 0 || (*door)->ray.v_intersect.y != 0)
    {
        v_dx = (*door)->ray.v_intersect.x - data->player.x;
        v_dy = (*door)->ray.v_intersect.y - data->player.y;
        (*door)->ray.v_dist = v_dx * v_dx + v_dy * v_dy;
    }
    else
    {
        (*door)->ray.v_dist = INFINITY;
    }

    if ((*door)->ray.h_dist < (*door)->ray.v_dist)
    {
        (*door)->ray.distance = sqrt((*door)->ray.h_dist);
        (*door)->ray.ray_end.x = (*door)->ray.h_intersect.x;
        (*door)->ray.ray_end.y = (*door)->ray.h_intersect.y;
    }
    else
    {
        (*door)->ray.distance = sqrt((*door)->ray.v_dist);
        (*door)->ray.ray_end.x = (*door)->ray.v_intersect.x;
        (*door)->ray.ray_end.y = (*door)->ray.v_intersect.y;
    }
    
    // Fix fisheye effect
    double angle_diff = (*door)->ray.ray_angle - data->player.angle;
    normalize_angle(&angle_diff);
    (*door)->ray.distance *= cos(angle_diff);
}

void calc_distance(t_data *data, t_ray *ray, t_door *door)
{
    // Reset door ray data if no door found
    if (!door->found_door)
    {
        door->ray.h_intersect.x = 0;
        door->ray.h_intersect.y = 0;
        door->ray.v_intersect.x = 0;
        door->ray.v_intersect.y = 0;
    }
    else
    {
        door->ray.ray_angle = ray->ray_angle;
    }

    calc_wall_distance(data, &ray, &door);
    calc_door_distance(data, &ray, &door);
    
    // Draw debug rays
    draw_line(data, ray->player, ray->ray_end, BLUE, 2);
    if (door->found_door)
    {
        draw_line(data, door->ray.player, door->ray.ray_end, YELLOW, 2);
    }
}