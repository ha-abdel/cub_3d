#include "cube_bonus.h"

void	set_wall_type(t_ray *ray)
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
}

void	copy_img(t_sprite *src, t_sprite **dst)
{
	(*dst)->addr = src->addr;
	(*dst)->width = src->width;
	(*dst)->height = src->height;
	(*dst)->bpp = src->bpp;
	(*dst)->line_len = src->line_len;
	(*dst)->img = src->img;
}
void	get_texture_img(t_data *data, t_ray *ray, t_sprite *img)
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
}

void	draw_wall_texture(t_data *data, t_ray *ray)
{
	t_sprite	img;
	t_texture	texture;
	int			y;

	y = ray->wall_start.y;
	get_texture_img(data, ray, &img);
	if (ray->h_dist < ray->v_dist)
		texture.wall_x = fmod(ray->ray_end.x, TILE_SIZE) / TILE_SIZE;
	else
		texture.wall_x = fmod(ray->ray_end.y, TILE_SIZE) / TILE_SIZE;
	texture.tex_x = (int)(texture.wall_x * (img.width - 1));
	texture.tex_step = img.height / ray->wall_strip;
	texture.tex_pos = (ray->wall_start.y - screen_height / 2 + ray->wall_strip
			/ 2) * texture.tex_step;
	while (y < ray->wall_end.y)
	{
		texture.tex_y = (int)texture.tex_pos % img.height;
		texture.pixel = img.addr + (texture.tex_y * img.line_len) + (texture.tex_x
				* (img.bpp / 8));
		texture.color = *(unsigned int *)texture.pixel;
		texture.tex_x = texture.tex_x % img.width;
		texture.tex_y = texture.tex_y % img.height;
		my_mlx_pixel_put(&data->bg1, ray->wall_start.x, y++, texture.color);
		texture.tex_pos += texture.tex_step;
	}
}


// void draw_door_texture(t_data *data, t_door *door) {
//     t_texture texture;
//     int y = door->ray.wall_start.y;

//     if (door->ray.h_dist < door->ray.v_dist)
//         texture.wall_x = fmod(door->ray.ray_end.x, TILE_SIZE) / TILE_SIZE;
//     else
//         texture.wall_x = fmod(door->ray.ray_end.y, TILE_SIZE) / TILE_SIZE;

//     texture.tex_x = (int)(texture.wall_x * (data->door.width - 1));
//     texture.tex_step = data->door.height / door->ray.wall_strip;
//     texture.tex_pos = (door->ray.wall_start.y - screen_height/2 + door->ray.wall_strip/2) * texture.tex_step;

//     while (y < door->ray.wall_end.y) {
//         texture.tex_y = (int)texture.tex_pos % data->door.height;
//         char *pixel = data->door.addr + (texture.tex_y * data->door.line_len) + 
//                      (texture.tex_x * (data->door.bpp / 8));
//         unsigned int color = *(unsigned int *)pixel;

//         // Only draw if not fully transparent
//         if (get_t(color) != 0xFF) {
//             my_mlx_pixel_put(&data->bg1, door->ray.wall_start.x, y, color);
//         }
        
//         texture.tex_pos += texture.tex_step;
//         y++;
//     }
// }

void draw_door_texture(t_data *data, t_door *door, t_ray *ray) {
    t_texture texture;
    int y = door->ray.wall_start.y;

    // Determine texture coordinates based on intersection side
    if (door->ray.h_dist < door->ray.v_dist) {
        texture.wall_x = fmod(door->ray.h_intersect.x, TILE_SIZE) / TILE_SIZE;
    } else {
        texture.wall_x = fmod(door->ray.v_intersect.y, TILE_SIZE) / TILE_SIZE;
    }

    texture.tex_x = (int)(texture.wall_x * (data->door.width - 1));
    texture.tex_step = data->door.height / door->ray.wall_strip;
    texture.tex_pos = (door->ray.wall_start.y - screen_height/2 + door->ray.wall_strip/2) * texture.tex_step;

    while (y < door->ray.wall_end.y) {
        texture.tex_y = (int)texture.tex_pos % data->door.height;
        char *pixel = data->door.addr + (texture.tex_y * data->door.line_len) + 
                     (texture.tex_x * (data->door.bpp / 8));
        unsigned int color = *(unsigned int *)pixel;

        // Only draw non-transparent pixels
        if (get_t(color) != 0xFF) {
            my_mlx_pixel_put(&data->bg1, door->ray.wall_start.x, y, color);
        }
		// else
        
        texture.tex_pos += texture.tex_step;
        y++;
    }
}
void	project_wall(t_ray **ray, int col)
{
	(*ray)->dist_projection_plane = (screen_width / 2.0) / tan((FOV / 2.0) * PI
			/ 180);
	(*ray)->wall_strip = (TILE_SIZE / (*ray)->distance) * (*ray)->dist_projection_plane;
	(*ray)->ceil = (screen_height) / 2 - (*ray)->wall_strip / 2;
	(*ray)->floor = (*ray)->ceil + (*ray)->wall_strip;
	if ((*ray)->ceil < 0)
		(*ray)->ceil = 0;
	if ((*ray)->floor > screen_height)
		(*ray)->floor = screen_height;
	(*ray)->wall_start.x = col;
	(*ray)->wall_start.y = (*ray)->ceil;
	(*ray)->wall_end.x = col;
	(*ray)->wall_end.y = (*ray)->floor;
	(*ray)->ceil_start.x = col;
	(*ray)->ceil_start.y = 0;
	(*ray)->ceil_end.x = col;
	(*ray)->ceil_end.y = (*ray)->ceil - 1;
	(*ray)->floor_start.x = col;
	(*ray)->floor_start.y = (*ray)->ceil + (*ray)->wall_strip;
	(*ray)->floor_end.x = col;
	(*ray)->floor_end.y = screen_height;
}
void	project_door(t_door **door, int col)
{
	(*door)->ray.dist_projection_plane = (screen_width / 2.0) / tan((FOV / 2.0) * PI
			/ 180);
	(*door)->ray.wall_strip = (TILE_SIZE / (*door)->ray.distance) * (*door)->ray.dist_projection_plane;
	(*door)->ray.ceil = (screen_height) / 2 - (*door)->ray.wall_strip / 2;
	(*door)->ray.floor = (*door)->ray.ceil + (*door)->ray.wall_strip;
	if ((*door)->ray.ceil < 0)
		(*door)->ray.ceil = 0;
	if ((*door)->ray.floor > screen_height)
		(*door)->ray.floor = screen_height;
	(*door)->ray.wall_start.x = col;
	(*door)->ray.wall_start.y = (*door)->ray.ceil;
	(*door)->ray.wall_end.x = col;
	(*door)->ray.wall_end.y = (*door)->ray.floor;
	(*door)->ray.ceil_start.x = col;
	(*door)->ray.ceil_start.y = 0;
	(*door)->ray.ceil_end.x = col;
	(*door)->ray.ceil_end.y = (*door)->ray.ceil - 1;
	(*door)->ray.floor_start.x = col;
	(*door)->ray.floor_start.y = (*door)->ray.ceil + (*door)->ray.wall_strip;
	(*door)->ray.floor_end.x = col;
	(*door)->ray.floor_end.y = screen_height;
}


void draw_wall_behind_door(t_data *data, t_ray *wall_ray, t_ray *door_ray)
{
	(void)door_ray;
    t_sprite wall_img;
    // t_texture texture;
    int y = wall_ray->wall_start.y;

    get_texture_img(data, wall_ray, &wall_img);

    double wall_x = (wall_ray->h_dist < wall_ray->v_dist)
        ? fmod(wall_ray->ray_end.x, TILE_SIZE) / TILE_SIZE
        : fmod(wall_ray->ray_end.y, TILE_SIZE) / TILE_SIZE;

    // double door_x = (door_ray->h_dist < door_ray->v_dist)
    //     ? fmod(door_ray->ray_end.x, TILE_SIZE) / TILE_SIZE
    //     : fmod(door_ray->ray_end.y, TILE_SIZE) / TILE_SIZE;

    int wall_tex_x = (int)(wall_x * (wall_img.width - 1));
    // int door_tex_x = (int)(door_x * (data->door.width - 1));
    double wall_tex_step = wall_img.height / wall_ray->wall_strip;
    double wall_tex_pos = (wall_ray->wall_start.y - screen_height / 2 + wall_ray->wall_strip / 2) * wall_tex_step;

    // double door_tex_step = data->door.height / door_ray->wall_strip;
    // double door_tex_pos = (door_ray->wall_start.y - screen_height / 2 + door_ray->wall_strip / 2) * door_tex_step;

    while (y < wall_ray->wall_end.y)
    {
        int wall_tex_y = ((int)wall_tex_pos) % wall_img.height;
        char *wall_pixel = wall_img.addr + (wall_tex_y * wall_img.line_len) + wall_tex_x * (wall_img.bpp / 8);
        unsigned int wall_color = *(unsigned int *)wall_pixel;

        // int door_tex_y = ((int)door_tex_pos) % data->door.height;
        // char *door_pixel = data->door.addr + (door_tex_y * data->door.line_len) + door_tex_x * (data->door.bpp / 8);
        // unsigned int door_color = *(unsigned int *)door_pixel;

        // draw wall only where door is transparent
        // if (get_t(door_color) == 0xFF)
        my_mlx_pixel_put(&data->bg1, wall_ray->wall_start.x, y, wall_color);

        wall_tex_pos += wall_tex_step;
        // door_tex_pos += door_tex_step;
        y++;
    }
}




// void wall_projection(t_data *data, t_ray *ray, int col, t_door *door) {
//     project_wall(&ray, col);
    
//     if (door->is_door) {
//         project_door(&door, col);
        
//         // Always draw the wall first (will be behind the door)
//         draw_wall_texture(data, ray);
        
//         // Then draw the door (transparent parts will show the wall)
//         draw_door_texture(data, door);
//     } else {
//         // No door, just draw the wall
//         draw_wall_texture(data, ray);
//     }
    
//     // Draw ceiling and floor
//     draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
//     draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
// }

// void wall_projection(t_data *data, t_ray *ray, int col, t_door *door) {
//     // Always project and draw the wall first (including walls behind doors)
//     project_wall(&ray, col);
//     draw_wall_texture(data, ray);
    
//     // If there's a door, project and draw it on top
//     if (door->is_door) {
		
//         // Save the original distance
//         // double original_dist = ray->distance;
        
//         // Temporarily use door distance for projection
//         // ray->distance = door->ray.distance;
//         project_wall(&ray, col);
//         draw_door_texture(data, door, ray);
        
//         // Restore original distance
//         // ray->distance = original_dist;
//     }
    
//     // Draw ceiling and floor
//     draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
//     draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
// }

// void wall_projection(t_data *data, t_ray *ray, int col, t_door *door)
// {
//     // 1) project & draw the wall
//     project_wall(&ray, col);
//     draw_wall_texture(data, ray);

//     // 2) if there’s a door and it’s closer, project & draw the door
//     if (door->found_door && door->ray.distance < ray->distance)
//     {
//         project_door(&door, col);
//         draw_door_texture(data, door, &door->ray);
//     }

//     // 3) ceiling & floor
//     draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
//     draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
// }
void wall_projection(t_data *data, t_ray *ray, int col, t_door *door)
{
	printf("wall dist is %0.2f ", ray->distance);
	printf("door dist is %0.2f \n", door->ray.distance);

    project_wall(&ray, col);
    if (door->found_door)
    {
        door->ray.ray_angle = ray->ray_angle;
        project_door(&door, col);

        if (door->ray.distance >= ray->distance)
        {
            // draw_wall_texture(data, ray);
            draw_wall_texture(data, ray);
			 draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
    		draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
			
        }
        else
        {
			 draw_line(data, door->ray.ceil_start, door->ray.ceil_end, data->map.c_color, 1);
   			 draw_line(data, door->ray.floor_start, door->ray.floor_end, data->map.f_color, 1);
			 draw_wall_texture(data, ray);
			 draw_door_texture(data, door, ray);
            
        }
    }
    else
    {
        draw_wall_texture(data, ray);
		draw_line(data, ray->ceil_start, ray->ceil_end, data->map.c_color, 1);
    	draw_line(data, ray->floor_start, ray->floor_end, data->map.f_color, 1);
    }

    // Draw ceiling and floor
   
}