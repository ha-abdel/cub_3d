#include "cube_bonus.h"

// void    part_one(t_ray **ray)
// {
//     // if ((*ray)->wall_type != NONE)
//     //     return ;
//     if (is_facing_up((*ray)->ray_angle))
//     {
//         if ((*ray)->h_dist < (*ray)->v_dist)
//             (*ray)->wall_type = S_WALL;
//         else
//         {
//             if (is_facing_right((*ray)->ray_angle))
//                 (*ray)->wall_type = E_WALL;
//             else
//                 (*ray)->wall_type = W_WALL;
//         }
//     }
//     else if (is_facing_down((*ray)->ray_angle))
//     {
//         if ((*ray)->h_dist < (*ray)->v_dist)
//             (*ray)->wall_type = N_WALL;
//         else
//         {
//             if (is_facing_left((*ray)->ray_angle))
//                 (*ray)->wall_type = W_WALL;
//             else
//                 (*ray)->wall_type = E_WALL;
//         }
//     }
// }
// void    part_two(t_ray **ray)
// {
//     // if ((*ray)->wall_type != NONE)
//     //     return ;
//     if (is_facing_right((*ray)->ray_angle))
//     {
//         if ((*ray)->h_dist < (*ray)->v_dist)
//             (*ray)->wall_type = E_WALL;
//         else
//         {
//             if (is_facing_down((*ray)->ray_angle))
//                 (*ray)->wall_type = N_WALL;
//             else
//                 (*ray)->wall_type = S_WALL;
//         }
//     }
//     else if (is_facing_left((*ray)->ray_angle))
//     {
//         if ((*ray)->h_dist < (*ray)->v_dist)
//             (*ray)->wall_type = W_WALL;
//         else
//         {
//             if (is_facing_up((*ray)->ray_angle))
//                 (*ray)->wall_type = S_WALL;
//             else
//                 (*ray)->wall_type = N_WALL;
//         }
//     }
// }

void    set_wall_type(t_ray *ray)
{
    if (ray->h_dist <= ray->v_dist)
    {
        if (is_facing_down(ray->ray_angle))
            ray->wall_type = N_WALL;
        else
            ray->wall_type = S_WALL;
    }
    else if (ray->h_dist > ray->v_dist)
    {
        if (is_facing_right(ray->ray_angle))
            ray->wall_type = E_WALL;
        else
            ray->wall_type = W_WALL;
    }
    // part_one(&ray);
    // if (ray->wall_type == NONE)
    //     part_two(&ray);
   
}

void    copy_img(t_sprite *src, t_sprite **dst)
{
    (*dst)->addr = src->addr;
    (*dst)->width = src->width;
    (*dst)->height = src->height;
    (*dst)->bpp = src->bpp;
    (*dst)->line_len = src->line_len;
    (*dst)->img = src->img;
}
void    get_texture_img(t_data *data, t_ray *ray, t_sprite *img)
{
    set_wall_type(ray);
    if (ray->wall_type == N_WALL)
        copy_img(&data->N_wall, &img);
    else if (ray->wall_type == S_WALL)
        copy_img(&data->S_wall, &img);
    else if (ray->wall_type == E_WALL)
        copy_img(&data->E_wall, &img);
    else if (ray->wall_type == W_WALL)
        copy_img(&data->W_wall, &img);
    // pixel = (*img).addr + (texture_offset_y * data->N_wall.line_len) + (texture_offset_x) * (data->N_wall.bpp / 8);
    // if (ray->wall_type == N_WALL)
    //     pixel = data->N_wall.addr + (texture_offset_y * data->N_wall.line_len) + 
    //         (texture_offset_x * (data->N_wall.bpp / 8));
    // else if (ray->wall_type == S_WALL)
    //     pixel = data->S_wall.addr + (texture_offset_y * data->S_wall.line_len) + 
    //         (texture_offset_x * (data->S_wall.bpp / 8));
    // if (ray->wall_type == E_WALL)
    //     pixel = data->E_wall.addr + (texture_offset_y * data->E_wall.line_len) + 
    //         (texture_offset_x * (data->E_wall.bpp / 8));
    // if (ray->wall_type == W_WALL)
    //     pixel = data->W_wall.addr + (texture_offset_y * data->W_wall.line_len) + 
    //         (texture_offset_x * (data->W_wall.bpp / 8));
    // printf("wall type is %d\n", ray->wall_type);
    // ray->color = *(unsigned int *)pixel;
}

void    draw_wall_texture(t_data *data, t_ray *ray)
{
    t_sprite img;
    char *pixel;
    unsigned int color = 0;
    int tex_x;
    int tex_y;
    double tex_step;
    double tex_pos;
    double wall_x;
    int y = ray->wall_start.y;

    get_texture_img(data, ray, &img);
    if (ray->h_dist < ray->v_dist)
        wall_x = fmod(ray->ray_end.x, TILE_SIZE) / TILE_SIZE;
    else
        wall_x = fmod(ray->ray_end.y, TILE_SIZE) / TILE_SIZE;
    tex_x = (int)(wall_x * (img.width - 1));

    tex_step = img.height / ray->wall_strip;
    tex_pos = (ray->wall_start.y - screen_height / 2 + ray->wall_strip / 2) * tex_step;
    while (y < ray->wall_end.y)
    {
        tex_y = (int)tex_pos % img.height;
        pixel = img.addr + (tex_y * img.line_len) + (tex_x * (img.bpp / 8));
        color = *(unsigned int *)pixel;
        tex_x = tex_x % img.width;
        tex_y = tex_y % img.height;
        my_mlx_pixel_put(&data->bg1, ray->wall_start.x, y, color);
        y++;
        tex_pos += tex_step;
    }
    
}

void    wall_projection(t_data *data, t_ray *ray, int *color, int col)
{
    (void)color;
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
    draw_wall_texture(data, ray);
    draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
    draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
}
