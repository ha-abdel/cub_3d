#include "../cube.h"

void    calc_first_v_intersect(t_data *data, t_ray *ray, double tan_val)
{
    if (is_facing_right(ray->ray_angle))
        ray->first_x = (floor(data->player.x / TILE_SIZE) + 1) * TILE_SIZE;
    else
        ray->first_x = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    ray->first_y = data->player.y + (ray->first_x - data->player.x) * tan_val;
}
void    calc_vertical_step(t_data *data, t_ray *ray, double tan_val)
{
    (void)data;
    if (is_facing_right(ray->ray_angle))
        ray->x_step = TILE_SIZE;
    else
        ray->x_step = -TILE_SIZE;
    ray->y_step = TILE_SIZE * fabs(tan_val);
    if (is_facing_up(ray->ray_angle))
        ray->y_step = -ray->y_step;
}

void check_vertical_intersect(t_data *data, t_ray *ray)
{
    double tan_val;
    normalize_angle(&ray->ray_angle);
    if (is_perpendicular_to_Xaxis(ray->ray_angle))
    {
        ray->v_intersect.x = data->player.x;
        if (is_facing_up(ray->ray_angle))
            ray->v_intersect.y = data->player.y + 3000;
        else
            ray->v_intersect.y = data->player.y - 3000;
        return ;
    }
    tan_val = tan(ray->ray_angle);
    calc_first_v_intersect(data, ray, tan_val);
    calc_vertical_step(data, ray, tan_val);
    ray->v_intersect.x = ray->first_x;
    ray->v_intersect.y = ray->first_y;
    while (!is_wall(data, ray->v_intersect.x - is_facing_left(ray->ray_angle), ray->v_intersect.y) && inside_bounds(data, ray->v_intersect.x, ray->v_intersect.y)) {
        ray->v_intersect.x += ray->x_step;
        ray->v_intersect.y += ray->y_step;
    }
}