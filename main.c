

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "libft/libft.h"
#include "cube.h"

//#define TILE_SIZE 64
//#define FOV 60.0
//#define NUM_RAYS 800
//#define PI 3.1415926535
//#define MAP_WIDTH 16
//#define MAP_HEIGHT 12
//#define PLAYER_SPEED 5
//#define ROTATION_SPEED 0.1

//// Color definitions
//#define WHITE 0xFFFFFF
//#define BLACK 0x000000
//#define RED 0xFF0000
//#define GREEN 0x00FF00
//#define BLUE 0x0000FF
//#define YELLOW 0xFFFF00
//#define GRAY 0x808080
//#define DARK_GRAY 0x404040

//#define PLAYER_NORTH 0
//#define PLAYER_SOUTH 1
//#define PLAYER_EAST 2
//#define PLAYER_WEST 3

//// Modified map with player marker
//static char *g_map[] = {
//    "1111111111111111",
//    "1000000000000001",
//    "1000000000000001",
//    "10000000000N0001",
//    "1000001000000001",
//    "1000000000000001",
//    "1001000000000001",
//    "1000000000000001",
//    "1000001000000001",
//    "1000000000000001",
//    "1000000000000001",
//    "1111111111111111",
//    NULL
//};


//typedef struct s_player {
//    double x;
//    double y;
//    double angle;
//} t_player;

//typedef struct s_data {
//    void *mlx;
//    void *win_3d;
//    void *win_2d;
//    t_player player;
//    int debug_ray_index; // Which ray to highlight in debug view
//} t_data;

//int is_wall(double x, double y) {
//    int grid_x = floor(x / TILE_SIZE);
//    int grid_y = floor(y / TILE_SIZE);
//    if (grid_x < 0 || grid_x >= MAP_WIDTH || grid_y < 0 || grid_y >= MAP_HEIGHT)
//        return 1;
//    return g_map[grid_y][grid_x] == '1';
//}

//void draw_square(t_data *data, int x, int y, int color, int win) {
//    for (int dy = 0; dy < TILE_SIZE; dy++) {
//        for (int dx = 0; dx < TILE_SIZE; dx++) {
//            if (win == 1)
//                mlx_pixel_put(data->mlx, data->win_3d, x + dx, y + dy, color);
//            else
//                mlx_pixel_put(data->mlx, data->win_2d, x + dx, y + dy, color);
//        }
//    }
//}

//void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color, int win) {
//    int dx = abs(x1 - x0);
//    int dy = abs(y1 - y0);
//    int sx = x0 < x1 ? 1 : -1;
//    int sy = y0 < y1 ? 1 : -1;
//    int err = (dx > dy ? dx : -dy) / 2;
//    int e2;

//    while (1) {
//        if (win == 1)
//            mlx_pixel_put(data->mlx, data->win_3d, x0, y0, color);
//        else
//            mlx_pixel_put(data->mlx, data->win_2d, x0, y0, color);
//        if (x0 == x1 && y0 == y1) break;
//        e2 = err;
//        if (e2 > -dx) { err -= dy; x0 += sx; }
//        if (e2 < dy) { err += dx; y0 += sy; }
//    }
//}

//// void draw_map(t_data *data) {
////     // Draw grid
////     for (int y = 0; y < MAP_HEIGHT; y++) {
////         for (int x = 0; x < MAP_WIDTH; x++) {
////             draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 
////                        g_map[y][x] == '1' ? DARK_GRAY : BLACK, 2);
////         }
////     }
    
////     // Draw grid lines
////     for (int x = 0; x <= MAP_WIDTH; x++) {
////         draw_line(data, x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, GRAY, 2);
////     }
////     for (int y = 0; y <= MAP_HEIGHT; y++) {
////         draw_line(data, 0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE, GRAY, 2);
////     }
    
////     // Draw player position
////     int px = (int)data->player.x;
////     int py = (int)data->player.y;
////     draw_square(data, px - 3, py - 3, RED, 2);
    
////     // Draw player direction
////     int dx = px + cos(data->player.angle) * 20;
////     int dy = py + sin(data->player.angle) * 20;
////     draw_line(data, px, py, dx, dy, GREEN, 2);
//// }

//void draw_wall_slice(t_data *data, int x, double distance, int ray_num) {
//    int screen_height = MAP_HEIGHT * TILE_SIZE;
//    int wall_height = (TILE_SIZE * 500) / distance;
//    int start_y = (screen_height - wall_height) / 2;
//    int end_y = start_y + wall_height;
    
//    if (start_y < 0) start_y = 0;
//    if (end_y > screen_height) end_y = screen_height;
    
//    // Color based on distance
//    int shade = 255 * (1 - distance / 800);
//    if (shade < 50) shade = 50;
//    int color = (shade << 16) | (shade << 8) | shade;
    
//    // Highlight the debug ray
//    if (ray_num == data->debug_ray_index) {
//        color = YELLOW;
//    }
    
//    for (int y = start_y; y < end_y; y++) {
//        mlx_pixel_put(data->mlx, data->win_3d, x, y, color);
//    }
//}


//void draw_map(t_data *data) {
//    // Draw grid and walls (same as before)
//    for (int y = 0; y < MAP_HEIGHT; y++) {
//        for (int x = 0; x < MAP_WIDTH; x++) {
//            draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 
//                       g_map[y][x] == '1' ? DARK_GRAY : BLACK, 2);
//        }
//    }
    
//    // Draw grid lines
//    for (int x = 0; x <= MAP_WIDTH; x++) {
//        draw_line(data, x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, GRAY, 2);
//    }
//    for (int y = 0; y <= MAP_HEIGHT; y++) {
//        draw_line(data, 0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE, GRAY, 2);
//    }
    
//    // Draw player position (center marker)
//    int px = (int)data->player.x;
//    int py = (int)data->player.y;
    
//    // Draw player as a red circle with direction indicator
//    for (int dy = -5; dy <= 5; dy++) {
//        for (int dx = -5; dx <= 5; dx++) {
//            if (dx*dx + dy*dy <= 25) // Circle equation
//                mlx_pixel_put(data->mlx, data->win_2d, px+dx, py+dy, RED);
//        }
//    }
    
//    // Draw direction line (longer for better visibility)
//    int dx = px + cos(data->player.angle) * 30;
//    int dy = py + sin(data->player.angle) * 30;
//    draw_line(data, px, py, dx, dy, GREEN, 2);
    
//    // Draw angle reference lines (0° and 90°)
//    draw_line(data, px, py, px + 50, py, WHITE, 2); // 0° reference (right)
//    draw_line(data, px, py, px, py + 50, WHITE, 2); // 90° reference (down)
//}

//void cast_rays(t_data *data) {
//    double ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
//    double angle_step = (FOV * PI / 180.0) / NUM_RAYS;
    
//    mlx_clear_window(data->mlx, data->win_3d);
    
//    for (int i = 0; i < NUM_RAYS; i++) {
//        double ray_x = data->player.x;
//        double ray_y = data->player.y;
//        double ray_dir_x = cos(ray_angle);
//        double ray_dir_y = sin(ray_angle);
//        double distance = 0;
        
//        while (!is_wall(ray_x, ray_y)) {
//            ray_x += ray_dir_x;
//            ray_y += ray_dir_y;
//            distance += 1;
//            if (distance > 1000) break;
            
//            // Draw ALL rays in debug view (faint blue)
//            mlx_pixel_put(data->mlx, data->win_2d, (int)ray_x, (int)ray_y, 0x3333AA);
//        }
        
//        // Highlight the selected ray in yellow
//        // if (i == data->debug_ray_index) {
//        //     draw_line(data, data->player.x, data->player.y, ray_x, ray_y, YELLOW, 2);
            
//        //     // Print detailed angle info
//        //     printf("\n--- Ray %d ---\n", i);
//        //     printf("Absolute Angle: %.2f° (0°=right, 90°=up)\n", ray_angle * 180/PI);
//        //     printf("Relative to Player: %.2f°\n", 
//        //           (ray_angle - data->player.angle) * 180/PI);
//        //     printf("Hit at: (%.2f, %.2f)\n", ray_x, ray_y);
//        //     printf("Raw Distance: %.2f\n", distance);
//        //     printf("Corrected Distance: %.2f\n", 
//        //           distance * cos(ray_angle - data->player.angle));
//        // }
        
//        distance *= cos(ray_angle - data->player.angle);
//        draw_wall_slice(data, i, distance, i);
//        ray_angle += angle_step;
//    }
    
//    // Draw angle markers in debug view
//    char angle_text[50];
//    sprintf(angle_text, "Player Angle: %.1f°", data->player.angle * 180/PI);
//    mlx_string_put(data->mlx, data->win_2d, 10, 20, WHITE, angle_text);
//}


//int handle_key(int key, t_data *data) {
//    if (key == 65307) { // ESC
//        mlx_destroy_window(data->mlx, data->win_3d);
//        mlx_destroy_window(data->mlx, data->win_2d);
//        exit(0);
//    }
    
//    // Movement
//    if (key == 119) { // W
//        data->player.x += cos(data->player.angle) * PLAYER_SPEED;
//        data->player.y += sin(data->player.angle) * PLAYER_SPEED;
//    }
//    if (key == 115) { // S
//        data->player.x -= cos(data->player.angle) * PLAYER_SPEED;
//        data->player.y -= sin(data->player.angle) * PLAYER_SPEED;
//    }
//    if (key == 97) { // A
//        data->player.x += sin(data->player.angle) * PLAYER_SPEED;
//        data->player.y -= cos(data->player.angle) * PLAYER_SPEED;
//    }
//    if (key == 100) { // D
//        data->player.x -= sin(data->player.angle) * PLAYER_SPEED;
//        data->player.y += cos(data->player.angle) * PLAYER_SPEED;
//    }
    
//    // Rotation
//    if (key == 65361)
//	{
//	 	data->player.angle -= ROTATION_SPEED;
//		if (data->player.angle < 0)
//			data->player.angle += 2 * PI;
//	}
		
//    if (key == 65363){
//		data->player.angle += ROTATION_SPEED; // Right
//		if (data->player.angle > 2 * PI)
//			data->player.angle -= 2 * PI;
//	}
    
//    // Debug controls
//    // if (key == 65451) data->debug_ray_index = (data->debug_ray_index + 1) % NUM_RAYS; // +
//    // if (key == 65453) data->debug_ray_index = (data->debug_ray_index - 1 + NUM_RAYS) % NUM_RAYS; // -
//    // if (key == 32) data->debug_ray_index = -1; // Space = show all rays
    
//    // Update both views
//    mlx_clear_window(data->mlx, data->win_2d);
//    draw_map(data);
//    cast_rays(data);
    
//    return 0;
//}

//void    init_data(t_data *data)
//{
//    data->map.c_color = -1;
//    data->map.f_color = -1;
//    data->map.direction = 0;
//    data->map.height = 0;
//    data->map.width = 0;
//    data->map.map = NULL;
//    data->player.angle = -1;
//    data->map.n_path = NULL;
//    data->map.s_path = NULL;
//    data->map.w_path = NULL;
//    data->map.e_path = NULL;
//    data->player.y = -1;
//    data->player.x = -1;
//}

void	my_mlx_pixel(t_sprite *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len) + x * (img->bpp / 8);
	*(unsigned int *)dst = color;
}

//void    cast_a_ray(t_data *data, int ray_angle)
//{
//    double     max_x;
//    double     max_y;
//    double     i;

//    max_x = data->player.x + cos(ray_angle) * 30;
//    max_y = data->player.y + cos(ray_angle) * 30;
//    i = data->player.x + 1;
//    while (i < max_x)
//    {
//        my_mlx_pixel(&data->bg, data->player.x + (i - data->player.x), data->player.y + (i - data->player.x), RED);
//        i++;
//    }
//}

//void cast_a_ray(t_data *data, double ray_angle)
//{
//    ray_angle =  fmod(ray_angle, 2 * PI);
//    //printf("ray_angle is %f\n",  ray_angle);
//    if (ray_angle < 0)
//        ray_angle += 2 * PI;
//    double x = data->player.x;
//    double y = data->player.y;
//    double step = 0.0;
//    double  flag;
    

//    //double dx = x + 60 * cos(ray_angle);
//    //double dy = y + 60 *  sin(ray_angle);
//    double dx = cos(ray_angle);
//    double dy = sin(ray_angle);

//    while (1)
//    {
//        flag = step / TILE_SIZE;
//        if (data->map.map)
//    }
//  while (step < 90)
//    {
//        my_mlx_pixel(&data->bg, x, y, BLUE);
//        x += dx;
//        y += dy;
//        step += 1.0;
//    }
//    //draw_line(data, x, y, dx, dy, BLUE, 2);
//}
double cast_a_ray(t_data *data, double ray_angle)
{
    // Normalize the angle between 0 and 2π
    ray_angle = fmod(ray_angle, 2 * PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;

    double x = data->player.x;
    double y = data->player.y;
    double step = 0.0;

    // Ray direction unit vector
    double dx = cos(ray_angle);
    double dy = sin(ray_angle);

    while (step < 1000)
    {
        if (is_wall(data, x, y))
            break;
        my_mlx_pixel(&data->bg, x, y, BLUE);

        x += dx;
        y += dy;
        step += 1.0;
    }

    return step; // This is the length of the ray
}



void    cast_my_rays(t_data *data)
{
    int colummnid;
    double ray_angle;

    colummnid = 0;
    ray_angle = (data->player.angle) - ((FOV / 2) * (PI / 180));
    while (colummnid < (data->map.width * TILE_SIZE))
    {
        cast_a_ray(data, ray_angle);
        ray_angle += (FOV * PI / 180) / (data->map.width * TILE_SIZE);
        colummnid++;
    }
    
}

int handle_key(int key, t_data *data) {
    if (key == ESC_KEY) {
        mlx_destroy_window(data->mlx, data->win_3d);
        mlx_destroy_window(data->mlx, data->win_2d);
        exit(0);
    }
    //clear_image(&data->bg, BLACK);
    // clear_image(&data->bg1, BLACK);

    
    if (key == W_KEY) {
        data->player.x += cos(data->player.angle) * PLAYER_SPEED;
        data->player.y += sin(data->player.angle) * PLAYER_SPEED;
    }
    if (key == S_KEY) {
        data->player.x -= cos(data->player.angle) * PLAYER_SPEED;
        data->player.y -= sin(data->player.angle) * PLAYER_SPEED;
    }
    if (key == A_KEY) {
        data->player.x += sin(data->player.angle) * PLAYER_SPEED;
        data->player.y -= cos(data->player.angle) * PLAYER_SPEED;
    }
    if (key == D_KEY) {
        data->player.x -= sin(data->player.angle) * PLAYER_SPEED;
        data->player.y += cos(data->player.angle) * PLAYER_SPEED;
    }
    
    if (key == LEFT_ARROW)
	{
	 	data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
		
    if (key == RIGHT_ARROW){
		data->player.angle += ROTATION_SPEED;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}
    
    // draw_map(data);
    // cast_rays(data);
    // mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
    // mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
    
    return 0;
}


//void    draw_player(t_sprite *img, int x, int y)
//{
//    int px = x;
//    int py = y;
//    int dy = -5;

//    while (dy <= 5)
//    {
//        int dx = -5;
//        while (dx <= 5)
//        {
//            if (dx*dx + dy*dy <= 25)
//                my_mlx_pixel_put(img, px+dx, py+dy, RED);
//            dx++;
//        }
//        dy++;
//    }
//}

//void draw_circle(t_data *data, t_sprite *img, int cx, int cy, int radius, int color)
//{
//    int x, y;
//    int r2 = radius * radius;
//    int thickness = 150; // border thickness

//    for (y = -radius; y <= radius; y++)
//    {
//        for (x = -radius; x <= radius; x++)
//        {
//            int dist2 = x * x + y * y;
//            if (dist2 >= r2 - thickness && dist2 <= r2 + thickness)
//                my_mlx_pixel(img, cx + x, cy + y, color);
//            //else if (dist2 <= r2 - thickness)
//                //mdraw_map(data, img, cx + x, cy + y);
//        }
//    }
//}


int    render(t_data *data)
{
    static int frame_counter;
    if (frame_counter == 60)
    {
        clear_image(&data->bg1, BLACK);
        clear_image(&data->bg, BLACK);

        draw_map(data);
        //cast_rays(data);
        cast_my_rays(data);
        mlx_put_image_to_window(data->mlx, data->win_2d, data->bg.img, 0, 0);
        create_minimap(data);
        mlx_put_image_to_window(data->mlx, data->win_3d, data->bg1.img, 0, 0);
        frame_counter = 0;
    }
    frame_counter++;

    return 0;
}

int main(int ac, char **av) {
    t_data data;
    (void)ac;
    
    initial_data(&data);
    main_function_parsing(&data, av[1]);
    init_data(&data);
    //draw_map(&data);
    //cast_my_rays(&data);
    //cast_rays(&data);
    // mlx_put_image_to_window(data.mlx, data.win_2d, data.bg.img, 0, 0);
    // mlx_put_image_to_window(data.mlx, data.win_3d, data.bg1.img, 0, 0);
    mlx_hook(data.win_3d, 2, 1L<<0, handle_key, &data);
    mlx_hook(data.win_2d, 2, 1L<<0, handle_key, &data);
    
    // printf("Controls:\n");
    // printf("WASD - Move\n");
    // printf("Arrow keys - Rotate\n");
    // printf("+/- - Select next/previous ray for debugging\n");
    // printf("Space - Show all rays\n");
    
   mlx_loop_hook(data.mlx, render, &data);
    mlx_loop(data.mlx);
    return 0;
}

// i need to create mini map
// first i need to make the mini map take only where the player
    // so i need to create a function that trac player and update the position
    // try to update in the circle only the place of player
// so will see the next:)