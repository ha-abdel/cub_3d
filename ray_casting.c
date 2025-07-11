#include "cube.h"

// Modified map with player marker
static char *g_map[] = {
    "1111111111111111",
    "1000000000000001",
    "1000000000000001",
    "10000000000N0001",
    "1000001000000001",
    "1000000000000001",
    "1001000000000001",
    "1000000000000001",
    "1000001000000001",
    "1000000000000001",
    "1000000000000001",
    "1111111111111111",
    NULL
};

//int is_wall(t_data *data, double x, double y) {
//    int grid_x = floor(x / TILE_SIZE);
//    int grid_y = floor(y / TILE_SIZE);
//    if (grid_x < 0 || grid_x >= data->map.width || grid_y < 0 || grid_y >= data->map.height || grid_x >= data->map.width || data->map.map[grid_y][grid_x] == '1')
//        return 1;
//    return (0);
//}


int is_wall(t_data *data, double x, double y)
{
    int grid_x = (int)(x / TILE_SIZE);
    int grid_y = (int)(y / TILE_SIZE);

    // Check for out-of-bounds access
    //printf("dx:[%.2f]/////dy:[%.2f]\n", x, y);
    //printf("x:[%d]/////y:[%d]\n", grid_x, grid_y);
    if (grid_x < 0 || grid_y < 0 || grid_y >= data->map.height || grid_x >= data->map.width)
        return 1;

    char c = data->map.map[grid_y][grid_x];
    
    // Treat walls and spaces as blocked
    if (c == '1' || c == ' ')
        return 1;

    return 0;
}


//int	check_for_obstacl(t_data *data, int y, int x, int end)
//{
//	while (x <= end)
//	{
//		if (data->map.map[y][x] == '1')
//			return (0);
//		x++;
//	}
//	return (1);
//}

//int	is_valid_pos(t_data *data, int new_x, int new_y)
//{
//	int	newr;
//	int	newl;
//	int	newd;
//	int	x;
//	int	y;

//	newr = (new_x + TILE_SIZE - 1) / TILE_SIZE;
//	newl = new_x / TILE_SIZE;
//	newd = (new_y + TILE_SIZE - 1) / TILE_SIZE;
//	y = new_y / TILE_SIZE;
//	while (y <= newd)
//	{
//		x = newl;
//		if (!check_for_obstacl(data, y, x, newr))
//			return (0);
//		y++;
//	}
//	return (1);
//}


int inside_bounds(t_data *data, double x, double y) {
    (void)data;
    if (x < 0 || x >= data->map.width * TILE_SIZE || y < 0 || y >= data->map.height * TILE_SIZE)
        return 0;
    return 1;
}



void	my_mlx_pixel_put(t_sprite *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len) + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

// Fill bg with black
void clear_image(t_sprite *img, int color) {
    //for (int y = 0; y < img->height; y++) {
    //    for (int x = 0; x < img->width; x++) {
    //        my_mlx_pixel_put(img, x, y, color);
    //    }
    //}
    int y = 0;
    int x;
    while (y < img->height)
    {
        x = 0;
        while (x < img->width)
        {
            my_mlx_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
}


void draw_square(t_data *data, int x, int y, int color, int win) {
    for (int dy = 0; dy < TILE_SIZE; dy++) {
        for (int dx = 0; dx < TILE_SIZE; dx++) {
            if (win == 1)
                my_mlx_pixel_put(&data->bg1, x + dx, y + dy, color);
            else
                my_mlx_pixel_put(&data->bg, x + dx, y + dy, color);
        }
    }
}

// breansham algorithm
// void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color, int win) {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = x0 < x1 ? 1 : -1;
//     int sy = y0 < y1 ? 1 : -1;
//     int err = (dx > dy ? dx : -dy) / 2;
//     int e2;

//     while (1) {
//         if (win == 1)
//             mlx_pixel_put(data->mlx, data->win_3d, x0, y0, color);
//         else
//             mlx_pixel_put(data->mlx, data->win_2d, x0, y0, color);
//         if (x0 == x1 && y0 == y1) break;
//         e2 = err;
//         if (e2 > -dx) { err -= dy; x0 += sx; }
//         if (e2 < dy) { err += dx; y0 += sy; }
//     }
// }
void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color, int win) {
    double dx = x1 - x0;
    double dy = y1 - y0;
    double steps = fmax(fabs(dx),fabs(dy));
    steps = fmin(steps, MAX_DIST_PIXEL);
    double inc_x = dx / steps;
    double inc_y = dy / steps;
    double x = x0;
    double y = y0;
    int i = 0;
    while (i < steps)
    {
        if (win == 1)
            my_mlx_pixel_put(&data->bg1, (int)x, (int)y, color);
        else
            my_mlx_pixel_put(&data->bg, (int)x, (int)y, color);
        i++;
        x+= inc_x;
        y+= inc_y;
    }
}

void    draw_walls(t_data *data)
{
    int y;
    int x;

    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 
                       data->map.map[y][x] == '1' ? BLACK : DARK_GRAY, 2);
            x++;
        }  
        y++;
    }
}

void    draw_grid_lines(t_data *data)
{
    int y = 0;
    int x = 0;

    while (x < data->map.width)
    {
        draw_line(data, x * TILE_SIZE, 0, x * TILE_SIZE, data->map.height * TILE_SIZE, GRAY, 2);
        x++;
    }
    while (y < data->map.height)
    {
        draw_line(data, 0, y * TILE_SIZE, data->map.width * TILE_SIZE, y * TILE_SIZE, GRAY, 2);
        y++;
    }

}
void    draw_player(t_data *data)
{
    int px = (int)data->player.x;
    int py = (int)data->player.y;
    int dy = -5;

    while (dy <= 5)
    {
        int dx = -5;
        while (dx <= 5)
        {
            if (dx*dx + dy*dy <= 25)
                my_mlx_pixel_put(&data->bg, px+dx, py+dy, RED);
            dx++;
        }
        dy++;
    }
}
void    draw_direction_lines(t_data *data)
{
    int px = (int)data->player.x;
    int py = (int)data->player.y;

    int dx = px + cos(data->player.angle) * 30;
    int dy = py + sin(data->player.angle) * 30;
    
    draw_line(data, px, py, dx, dy, GREEN, 2);
}

void draw_map(t_data *data) {
    draw_walls(data);
    //draw_grid_lines(data);
    draw_player(data);
   // draw_direction_lines(data);
    draw_line(data, data->player.x, data->player.y, data->player.x + 50, data->player.y, WHITE, 2); // 0° reference (right)
    draw_line(data, data->player.x, data->player.y, data->player.x, data->player.y + 50, WHITE, 2); // 90° reference (down)
    // mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
    // mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
}


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

void check_horizontal_intersect(t_data *data, double *x_intersect, double *y_intersect, double ray_angle) {
    ray_angle = fmod(ray_angle, 2 * PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    // call function normalize angle

    if (is_perpendicular_to_Yaxis(ray_angle))
    {
        if (is_facing_right(ray_angle))
            *x_intersect = data->player.x + 3000;
        else
            *x_intersect = data->player.x - 3000;
        *y_intersect = data->player.y;
        return;
    }
    double tan_val = tan(ray_angle);
    if (fabs(tan_val) <= 0.0001)
        tan_val = (tan_val >= 0) ? 0.0001 : -0.0001;

    double first_y;
    double y_step;
    if (is_facing_up(ray_angle)) {
        first_y = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
        y_step = -TILE_SIZE;
    } else {
        first_y = (floor(data->player.y / TILE_SIZE) + 1) * TILE_SIZE;
        y_step = TILE_SIZE;
    }
    double first_x = data->player.x + (first_y - data->player.y) / tan_val;
    double x_step = TILE_SIZE / fabs(tan_val);
    if (is_facing_left(ray_angle))
        x_step = -x_step;
    *x_intersect = first_x;
    *y_intersect = first_y;

    while (!is_wall(data, *x_intersect, *y_intersect - is_facing_up(ray_angle)) && inside_bounds(data, *x_intersect, *y_intersect)) {
        *x_intersect += x_step;
        *y_intersect += y_step;
    }
}

void check_vertical_intersect(t_data *data, double *x_intersect, double *y_intersect, double ray_angle) {
    ray_angle = fmod(ray_angle, 2 * PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    // call function normalise angle 

    if (is_perpendicular_to_Xaxis(ray_angle))
    {
        *x_intersect = data->player.x;
        if (is_facing_up(ray_angle))
            *y_intersect = data->player.y + 3000;
        else
            *y_intersect = data->player.y - 3000;
        return ;
    }
    double tan_val = tan(ray_angle);
    double first_x;
    double x_step;
    if (is_facing_right(ray_angle))
    {
        first_x = (floor(data->player.x / TILE_SIZE) + 1) * TILE_SIZE;
        x_step = TILE_SIZE;
    } else
    {
        first_x = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
        x_step = -TILE_SIZE;
    }
    double first_y = data->player.y + (first_x - data->player.x) * tan_val;
    double y_step = TILE_SIZE * fabs(tan_val);
    if (is_facing_up(ray_angle))
        y_step = -y_step;
    *x_intersect = first_x;
    *y_intersect = first_y;
    while (!is_wall(data, *x_intersect - is_facing_left(ray_angle), *y_intersect) && inside_bounds(data, *x_intersect, *y_intersect)) {
        *x_intersect += x_step;
        *y_intersect += y_step;
    }
}

void cast_rays(t_data *data) {
    // clear_image(&data->bg1, BLACK);
    double ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    double angle_step = (FOV * PI / 180.0) / NUM_RAYS;
    double distance = 0;

    for (int i = 0; i < NUM_RAYS; i++) {
        double hx, hy;
        double vx, vy;
        check_horizontal_intersect(data, &hx, &hy, ray_angle);
        check_vertical_intersect(data, &vx, &vy, ray_angle);

        double h_dist = (hx - data->player.x) * (hx - data->player.x) + (hy - data->player.y) * (hy - data->player.y);
        double v_dist = (vx - data->player.x) * (vx - data->player.x) + (vy - data->player.y) * (vy - data->player.y);
        int color;
        double ray_end_x, ray_end_y;
        if (h_dist < v_dist) {
            color = RED;
            distance = sqrt(h_dist);
            ray_end_x = hx;
            ray_end_y = hy;
        } else {
            color = BLUE;
            distance = sqrt(v_dist);
            ray_end_x = vx;
            ray_end_y = vy;
        }
        distance *= cos(ray_angle - data->player.angle);
        draw_line(data, data->player.x, data->player.y, ray_end_x, ray_end_y, BLUE, 2);
        double dist_projection_plane = ((data->map.width * TILE_SIZE) / 2) / tan ((FOV / 2) * PI / 180);
        // double dist_projection_plane = 2;
        double wall_strip = (TILE_SIZE / distance) * dist_projection_plane ;

        // draw_line(data, i , ((data->map.height * TILE_SIZE) / 2) - (wall_strip / 2), i,(wall_strip / 2)  + wall_strip, WHITE, 1);
        int wall_top = (data->map.height * TILE_SIZE) / 2 - wall_strip / 2;
        int wall_bottom = wall_top + wall_strip;
        draw_line(data, i, wall_top, i, wall_bottom, color, 1);

        ray_angle += angle_step;
    }
    // clear_image(data->bg1.img, BLACK);
    // mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
}


//int handle_key(int key, t_data *data) {
//    if (key == ESC_KEY) {
//        mlx_destroy_window(data->mlx, data->win_3d);
//        mlx_destroy_window(data->mlx, data->win_2d);
//        exit(0);
//    }
//    // clear_image(&data->bg, BLACK);
//    // clear_image(&data->bg1, BLACK);

    
//    if (key == W_KEY) {
//        data->player.x += cos(data->player.angle) * PLAYER_SPEED;
//        data->player.y += sin(data->player.angle) * PLAYER_SPEED;
//    }
//    if (key == S_KEY) {
//        data->player.x -= cos(data->player.angle) * PLAYER_SPEED;
//        data->player.y -= sin(data->player.angle) * PLAYER_SPEED;
//    }
//    if (key == A_KEY) {
//        data->player.x += sin(data->player.angle) * PLAYER_SPEED;
//        data->player.y -= cos(data->player.angle) * PLAYER_SPEED;
//    }
//    if (key == D_KEY) {
//        data->player.x -= sin(data->player.angle) * PLAYER_SPEED;
//        data->player.y += cos(data->player.angle) * PLAYER_SPEED;
//    }
    
//    if (key == LEFT_ARROW)
//	{
//	 	data->player.angle -= ROTATION_SPEED;
//		if (data->player.angle < 0)
//			data->player.angle += 2 * PI;
//	}
		
//    if (key == RIGHT_ARROW){
//		data->player.angle += ROTATION_SPEED;
//		if (data->player.angle > 2 * PI)
//			data->player.angle -= 2 * PI;
//	}
    
//    // draw_map(data);
//    // cast_rays(data);
//    // mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
//    // mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
    
//    return 0;
//}

void    init_data(t_data *data)
{
    data->mlx = mlx_init();
    data->win_3d = mlx_new_window(data->mlx, NUM_RAYS, data->map.height * TILE_SIZE, "3D View");
    data->win_2d = mlx_new_window(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE, "2D Debug View");

    data->bg.img = mlx_new_image(data->mlx, data->map.width * TILE_SIZE, data->map.height * TILE_SIZE);
    data->bg.addr = mlx_get_data_addr(data->bg.img, &data->bg.bpp, &data->bg.line_len, &data->bg.endian);
    data->bg.width = data->map.width * TILE_SIZE;
    data->bg.height = data->map.height * TILE_SIZE;
    data->bg1.img = mlx_new_image(data->mlx, NUM_RAYS, data->map.height * TILE_SIZE);
    data->bg1.addr = mlx_get_data_addr(data->bg1.img, &data->bg1.bpp, &data->bg1.line_len, &data->bg1.endian);
    data->bg1.width = NUM_RAYS;
    data->bg1.height = data->map.height * TILE_SIZE;


    
    data->player.x = TILE_SIZE * data->player.x;
    data->player.y = TILE_SIZE * data->player.y;
    //data->player.angle = PI / 2;
    // data->debug_ray_index = NUM_RAYS / 2;
    // data->player.is_facing_down = 0;
    // data->player.is_facing_up = 0;
    // data->player.is_facing_right = 0;
    // data->player.is_facing_left = 0;

    // if (data->player.angle >= 0 && data->player.angle <= PI / 2)
    //     data->player.is_facing_down = 1;
    // else
    //     data->player.is_facing_up = 1;
    // if (data->player.angle >= PI / 2 && data->player.angle <= 1.5 * PI)
    //     data->player.is_facing_left = 1;
    // else
    //     data->player.is_facing_right = 1;
}


//int    render(t_data *data)
//{
//    static int frame_counter;
//    if (frame_counter == 60)
//    {
//        clear_image(&data->bg1, BLACK);
//        clear_image(&data->bg, BLACK);

//        draw_map(data);
//        cast_rays(data);
//        mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
//        mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
//        frame_counter = 0;
//    }
//    frame_counter++;

//    return 0;
//}
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

//int main(int ac, char **av) {
//    t_data data;
//    (void)ac;
    
//    initial_data(&data);
//    main_function_parsing(&data, av[1]);
//    init_data(&data);
//    draw_map(&data);
//    cast_rays(&data);
//    // mlx_put_image_to_window(data.mlx, data.win_2d, data.bg.img, 0, 0);
//    // mlx_put_image_to_window(data.mlx, data.win_3d, data.bg1.img, 0, 0);
//    mlx_hook(data.win_3d, 2, 1L<<0, handle_key, &data);
//    mlx_hook(data.win_2d, 2, 1L<<0, handle_key, &data);
    
//    // printf("Controls:\n");
//    // printf("WASD - Move\n");
//    // printf("Arrow keys - Rotate\n");
//    // printf("+/- - Select next/previous ray for debugging\n");
//    // printf("Space - Show all rays\n");
    
//   mlx_loop_hook(data.mlx, render, &data);
//    mlx_loop(data.mlx);
//    return 0;
//}