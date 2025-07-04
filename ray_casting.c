#include "cube.h"

int is_facing_up(double angle)
{
    if (angle >= PI)
        return 1;
    return 0;
}
int is_facing_down(double angle)
{
    if (angle > 0 && angle < PI)
        return 1;
    return 0;
}
int is_facing_left(double angle)
{
    if (angle > PI / 2 && angle < 1.5 *PI)
        return 1;
    return 0;
}
int is_facing_right(double angle)
{
    if (angle >= 1.5 * PI || angle <= PI / 2)
        return 1;
    return 0;
}

int is_perpendicular_to_Yaxis(double ray_angle)
{
    if (ray_angle == 0 || ray_angle == PI)
        return 1;
    return 0;
}
int is_perpendicular_to_Xaxis(double ray_angle)
{
    if (ray_angle == 1.5 * PI || ray_angle == PI / 2)
        return 1;
    return 0;
}

void    normalize_angle(double *angle)
{
    (*angle) = fmod(*angle, 2 * PI);
    if (*angle < 0)
        (*angle) += 2 * PI;
}

void    calc_first_h_intersect(t_data *data, t_ray *ray, double tan_val)
{
    if (is_facing_up(ray->ray_angle))
        ray->first_y = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    else
        ray->first_y = (floor(data->player.y / TILE_SIZE) + 1) * TILE_SIZE;
    ray->first_x = data->player.x + (ray->first_y - data->player.y) / tan_val;
}
void    calc_horizontal_step(t_data *data, t_ray *ray, double tan_val)
{
    (void)data;
    if (is_facing_up(ray->ray_angle))
        ray->y_step = -TILE_SIZE;
    else
        ray->y_step = TILE_SIZE;
    ray->x_step = TILE_SIZE / fabs(tan_val);
    if (is_facing_left(ray->ray_angle))
        ray->x_step = -(ray->x_step);
}
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

void check_horizontal_intersect(t_data *data, t_ray *ray)
{
    double tan_val;
    normalize_angle(&ray->ray_angle);
    if (is_perpendicular_to_Yaxis(ray->ray_angle))
    {
        if (is_facing_right(ray->ray_angle))
            (ray->h_intersect).x = data->player.x + 3000;
        else
            (ray->h_intersect).x = data->player.x - 3000;
        (ray->h_intersect).y = data->player.y;
        return;
    }
    tan_val = tan(ray->ray_angle);
    if (fabs(tan_val) <= 0.000001)
    {
        if (tan_val >= 0)
            tan_val = 0.000001;
        else
            tan_val = -0.000001;
    }
    calc_first_h_intersect(data, ray, tan_val);
    calc_horizontal_step(data, ray, tan_val);
    (ray->h_intersect).x = ray->first_x;
    (ray->h_intersect).y = ray->first_y;
    while (!is_wall(data, (ray->h_intersect).x, (ray->h_intersect).y - is_facing_up(ray->ray_angle)) && inside_bounds(data, (ray->h_intersect).x, (ray->h_intersect).y)) {
        (ray->h_intersect).x += ray->x_step;
        (ray->h_intersect).y += ray->y_step;
    }
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

void    calc_distance(t_data *data, t_ray *ray, int *color)
{
    ray->h_dist = (ray->h_intersect.x - data->player.x) * (ray->h_intersect.x - data->player.x) + (ray->h_intersect.y - data->player.y) * (ray->h_intersect.y - data->player.y);
    ray->v_dist = (ray->v_intersect.x - data->player.x) * (ray->v_intersect.x - data->player.x) + (ray->v_intersect.y - data->player.y) * (ray->v_intersect.y - data->player.y);

    if (ray->h_dist < ray->v_dist)
    {
        *color = GREEN;
        ray->distance = sqrt(ray->h_dist);
        ray->ray_end.x = ray->h_intersect.x;
        ray->ray_end.y = ray->h_intersect.y;
    } else 
    {
        *color = WHITE;
        ray->distance = sqrt(ray->v_dist);
        ray->ray_end.x = ray->v_intersect.x;
        ray->ray_end.y = ray->v_intersect.y;
    }
    ray->distance *= cos(ray->ray_angle - data->player.angle);
    draw_line(data, ray->player, ray->ray_end, BLUE, 2);
}

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

void    init_ray(t_ray *ray, t_data *data)
{
    ray->ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    ray->angle_step = (FOV * PI / 180.0) / NUM_RAYS;
    ray->distance = 0;
    ray->player.x = data->player.x;
    ray->player.y = data->player.y;
}

void cast_rays(t_data *data)
{
    t_ray   ray;
    int     i;
    int     color;
    
    i = 0;
    init_ray(&ray, data);

    while (i < NUM_RAYS)
    {
        check_horizontal_intersect(data, &ray);
        check_vertical_intersect(data, &ray);
        calc_distance(data, &ray, &color);
        wall_projection(data, &ray, &color, i);
        ray.ray_angle += ray.angle_step;
        i++;
    }
}


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
    data->player.x = TILE_SIZE * data->player.x + TILE_SIZE / 2;
    data->player.y = TILE_SIZE * data->player.y + TILE_SIZE / 2;

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
}
