

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TILE_SIZE 64
#define FOV 60.0
#define NUM_RAYS 1
#define PI 3.1415926535
#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define PLAYER_SPEED 5
#define ROTATION_SPEED 0.1

// Color definitions
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define GRAY 0x808080
#define DARK_GRAY 0x404040

#define PLAYER_NORTH 0
#define PLAYER_SOUTH 1
#define PLAYER_EAST 2
#define PLAYER_WEST 3

#define RIGHT_ARROW 65363
#define LEFT_ARROW 65361

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


typedef struct s_player {
    double x;
    double y;
    double angle;
    int is_facing_up;
    int is_facing_down;
    int is_facing_right;
    int is_facing_left;
} t_player;

typedef struct s_data {
    void *mlx;
    void *win_3d;
    void *win_2d;
    t_player player;
    int debug_ray_index; // Which ray to highlight in debug view
} t_data;

int is_wall(double x, double y) {
    int grid_x = floor(x / TILE_SIZE);
    int grid_y = floor(y / TILE_SIZE);
    if (grid_x < 0 || grid_x >= MAP_WIDTH || grid_y < 0 || grid_y >= MAP_HEIGHT)
        return 1;
    return g_map[grid_y][grid_x] == '1';
}

int inside_bounds(t_data *data, double x, double y) {
    (void)data;
    if (x < 0 || x >= MAP_WIDTH * TILE_SIZE || y < 0 || y >= MAP_HEIGHT * TILE_SIZE)
        return 0;
    return 1;
}

// void	my_mlx_pixel_put(t_sprite *img, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
// 		return ;
// 	dst = img->addr + (y * img->line_len) + x * (img->bpp / 8);
// 	*(unsigned int *)dst = color;
// }

void draw_square(t_data *data, int x, int y, int color, int win) {
    for (int dy = 0; dy < TILE_SIZE; dy++) {
        for (int dx = 0; dx < TILE_SIZE; dx++) {
            if (win == 1)
                mlx_pixel_put(data->mlx, data->win_3d, x + dx, y + dy, color);
            else
                mlx_pixel_put(data->mlx, data->win_2d, x + dx, y + dy, color);
        }
    }
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color, int win) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        if (win == 1)
            mlx_pixel_put(data->mlx, data->win_3d, x0, y0, color);
        else
            mlx_pixel_put(data->mlx, data->win_2d, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

// void draw_map(t_data *data) {
//     // Draw grid
//     for (int y = 0; y < MAP_HEIGHT; y++) {
//         for (int x = 0; x < MAP_WIDTH; x++) {
//             draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 
//                        g_map[y][x] == '1' ? DARK_GRAY : BLACK, 2);
//         }
//     }
    
//     // Draw grid lines
//     for (int x = 0; x <= MAP_WIDTH; x++) {
//         draw_line(data, x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, GRAY, 2);
//     }
//     for (int y = 0; y <= MAP_HEIGHT; y++) {
//         draw_line(data, 0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE, GRAY, 2);
//     }
    
//     // Draw player position
//     int px = (int)data->player.x;
//     int py = (int)data->player.y;
//     draw_square(data, px - 3, py - 3, RED, 2);
    
//     // Draw player direction
//     int dx = px + cos(data->player.angle) * 20;
//     int dy = py + sin(data->player.angle) * 20;
//     draw_line(data, px, py, dx, dy, GREEN, 2);
// }

void draw_wall_slice(t_data *data, int x, double distance, int ray_num) {
    int screen_height = MAP_HEIGHT * TILE_SIZE;
    int wall_height = (TILE_SIZE * 500) / distance;
    int start_y = (screen_height - wall_height) / 2;
    int end_y = start_y + wall_height;
    
    if (start_y < 0) start_y = 0;
    if (end_y > screen_height) end_y = screen_height;
    
    // Color based on distance
    int shade = 255 * (1 - distance / 800);
    if (shade < 50) shade = 50;
    int color = (shade << 16) | (shade << 8) | shade;
    
    // Highlight the debug ray
    if (ray_num == data->debug_ray_index) {
        color = YELLOW;
    }
    
    for (int y = start_y; y < end_y; y++) {
        mlx_pixel_put(data->mlx, data->win_3d, x, y, color);
    }
}

void    draw_walls(t_data *data)
{
    int y;
    int x;

    y = 0;
    while (y < MAP_HEIGHT)
    {
        x = 0;
        while (x < MAP_WIDTH)
        {
            draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 
                       g_map[y][x] == '1' ? DARK_GRAY : BLACK, 2);
            x++;
        }  
        y++;
    }
}

void    draw_grid_lines(t_data *data)
{
    int y = 0;
    int x = 0;

    while (x < MAP_WIDTH)
    {
        draw_line(data, x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, GRAY, 2);
        x++;
    }
    while (y < MAP_HEIGHT)
    {
        draw_line(data, 0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE, GRAY, 2);
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
                mlx_pixel_put(data->mlx, data->win_2d, px+dx, py+dy, RED);
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
    draw_grid_lines(data);
    draw_player(data);
    draw_direction_lines(data);
    draw_line(data, data->player.x, data->player.y, data->player.x + 50, data->player.y, WHITE, 2); // 0° reference (right)
    draw_line(data, data->player.x, data->player.y, data->player.x, data->player.y + 50, WHITE, 2); // 90° reference (down)
}
/*
void check_horizontal_intersect(t_data *data, double *x_intersect, double *y_intersect, double ray_angle) {
    // ray_angle = fmod(ray_angle, 2*PI);
    if (ray_angle < 0)
        ray_angle += 2*PI;
    if (ray_angle > 2*PI)
        ray_angle -= 2*PI;

    double tan_val = tan(ray_angle);
    if (tan_val == 0)
        tan_val = 0.0001;  // Avoid division by zero

    // Calculate first y intersection
    double first_y;
    double y_step;
    if (ray_angle > PI) { // Facing up
        first_y = (floor(data->player.y / TILE_SIZE) * TILE_SIZE) - 1;
        y_step = -TILE_SIZE;
    } else { // Facing down
        first_y = (floor(data->player.y / TILE_SIZE) + 1) * TILE_SIZE;
        y_step = TILE_SIZE;
    }

    // Calculate first x intersection
    double first_x = data->player.x + (data->player.y - first_y) / tan_val;
    
    // Calculate x step
    double x_step = TILE_SIZE / fabs(tan_val);
    if ((ray_angle > PI/2 && ray_angle < 3*PI/2)) {
        x_step = -x_step; // Facing left
    }
    *x_intersect = first_x;
    *y_intersect = first_y;

    // Find wall hit
    while (!is_wall(*x_intersect, *y_intersect) && inside_bounds(data, *x_intersect, *y_intersect)) {
        if (!inside_bounds(data, (*x_intersect) + x_step, (*y_intersect)+ y_step))
            return ;
        *x_intersect += x_step;
        *y_intersect += y_step;
    }
}
*/
void check_horizontal_intersect(t_data *data, double *x_intersect, double *y_intersect, double ray_angle) {
    ray_angle = fmod(ray_angle, 2 * PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;

    // Handle cases where ray is exactly horizontal (0 or PI)
    if (ray_angle == 0 || ray_angle == PI) {
        *x_intersect = data->player.x + (ray_angle == 0 ? 1000 : -1000); // Arbitrary large distance
        *y_intersect = data->player.y;
        return;
    }

    double tan_val = tan(ray_angle);
    if (fabs(tan_val) <= 0) tan_val = 0.0001;  // Avoid division by near-zero

    // Calculate first y intersection
    double first_y;
    double y_step;
    if (ray_angle > PI) { // Facing up
        first_y = floor(data->player.y / TILE_SIZE) * TILE_SIZE - 1;
        y_step = -TILE_SIZE;
    } else { // Facing down
        first_y = (floor(data->player.y / TILE_SIZE) + 1) * TILE_SIZE;
        y_step = TILE_SIZE;
    }

    // Calculate first x intersection
    double first_x = data->player.x + (first_y - data->player.y) / tan_val;
    
    // Calculate x step
    double x_step = TILE_SIZE / fabs(tan_val);
    if ((ray_angle > PI/2 && ray_angle < 3*PI/2)) {
        x_step = -x_step; // Facing left
    }

    *x_intersect = first_x;
    *y_intersect = first_y;

    // Find wall hit
    while (!is_wall(*x_intersect, *y_intersect) && inside_bounds(data, *x_intersect, *y_intersect)) {
        *x_intersect += x_step;
        *y_intersect += y_step;
    }
}

// void check_vertical_intersect(t_data *data, double *x_intersect, double *y_intersect, double ray_angle) {
//     // ray_angle = fmod(ray_angle, 2*PI);
//     if (ray_angle < 0)
//         ray_angle += 2*PI;
//     if (ray_angle > 2*PI)
//         ray_angle -= 2*PI;

//     double tan_val = tan(ray_angle);
//     if (tan_val == 0)
//         tan_val = 0.0001;  // Avoid division by zero

//     // Calculate first y intersection
//     double first_x;
//     double y_step;
//     if (ray_angle < PI / 2 || ray_angle > 1.5 * PI) { // Facing right
//         first_x = (floor(data->player.y / TILE_SIZE + 1) * TILE_SIZE);
//         y_step = -TILE_SIZE;
//     } else { // Facing left
//         first_x = (floor(data->player.y / TILE_SIZE)) * TILE_SIZE;
//         y_step = TILE_SIZE;
//     }

//     // Calculate first x intersection
//     double first_y = data->player.x + (data->player.y - first_y) / tan_val;
    
//     // Calculate x step
//     double x_step = TILE_SIZE / fabs(tan_val);
//     if ((ray_angle > PI/2 && ray_angle < 3*PI/2)) {
//         x_step = -x_step; // Facing left
//     }
//     *x_intersect = first_x;
//     *y_intersect = first_y;

//     // Find wall hit
//     while (!is_wall(*x_intersect, *y_intersect)) {
//         if (*x_intersect <= 0 || *x_intersect >= 800 
//         * TILE_SIZE || *y_intersect <= 0 || *y_intersect >= 800)
//             return;
//         *x_intersect += x_step;
//         *y_intersect += y_step;
//     }
// }

// void cast_rays(t_data *data) {
//     double ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
//     double angle_step = (FOV * PI / 180.0) / NUM_RAYS;
    
//     // mlx_clear_window(data->mlx, data->win_2d);
//     // draw_map(data);
    
//     for (int i = 0; i < NUM_RAYS; i++) {
//         double ray_end_x, ray_end_y;
//         check_horizontal_intersect(data, &ray_end_x, &ray_end_y, ray_angle);
//         // double dx = ray_end_x - data->player.x;
//         // double dy = ray_end_y - data->player.y;
//         // double ray_dist = sqrt(dx*dx + dy*dy);
        
//         // printf("ray_angle is %f\n", ray_angle * 180 / PI);
//         // printf("intersect x %f\n", ray_end_x);
//         // printf("intersect y %f\n", ray_end_y);
//         draw_line(data, data->player.x, data->player.y, ray_end_x, ray_end_y, BLUE, 2);
//         ray_angle += angle_step;
//     }
// }
void check_vertical_intersect(t_data *data, double *x_intersect, double *y_intersect, double ray_angle) {
    ray_angle = fmod(ray_angle, 2 * PI);
    if (ray_angle < 0) ray_angle += 2 * PI;

    // Handle cases where ray is exactly vertical (PI/2 or 3PI/2)
    if (ray_angle == PI/2 || ray_angle == 3*PI/2) {
        *x_intersect = data->player.x;
        *y_intersect = data->player.y + (ray_angle == PI/2 ? 1000 : -1000);
        return;
    }

    double tan_val = tan(ray_angle);
    // if (fabs(tan_val) > 1e6) tan_val = 1e6;  // Avoid extreme values

    // Calculate first x intersection
    double first_x;
    double x_step;
    if (ray_angle < PI/2 || ray_angle > 3*PI/2) { // Facing right
        first_x = (floor(data->player.x / TILE_SIZE) + 1) * TILE_SIZE;
        x_step = TILE_SIZE;
    } else { // Facing left
        first_x = floor(data->player.x / TILE_SIZE) * TILE_SIZE - 1;
        x_step = -TILE_SIZE;
    }

    // Calculate first y intersection
    double first_y = data->player.y + (first_x - data->player.x) * tan_val;
    
    // Calculate y step
    double y_step = TILE_SIZE * fabs(tan_val);
    if (ray_angle > PI) {
        y_step = -y_step; // Facing up
    }

    *x_intersect = first_x;
    *y_intersect = first_y;

    // Find wall hit
    while (!is_wall(*x_intersect, *y_intersect) && inside_bounds(data, *x_intersect, *y_intersect)) {
        *x_intersect += x_step;
        *y_intersect += y_step;
    }
}

void cast_rays(t_data *data) {
    double ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    double angle_step = (FOV * PI / 180.0) / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        double hx, hy; // Horizontal intersection
        double vx, vy; // Vertical intersection

        check_horizontal_intersect(data, &hx, &hy, ray_angle);
        check_vertical_intersect(data, &vx, &vy, ray_angle);

        // Calculate distances
        double h_dist = (hx - data->player.x) * (hx - data->player.x) + (hy - data->player.y) * (hy - data->player.y);
        double v_dist = (vx - data->player.x) * (vx - data->player.x) + (vy - data->player.y) * (vy - data->player.y);

        // Choose the closest intersection
        double ray_end_x, ray_end_y;
        if (h_dist < v_dist) {
            ray_end_x = hx;
            ray_end_y = hy;
        } else {
            ray_end_x = vx;
            ray_end_y = vy;
        }

        draw_line(data, data->player.x, data->player.y, ray_end_x, ray_end_y, BLUE, 2);
        ray_angle += angle_step;
    }
}
// void cast_rays(t_data *data) {
//     double ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
//     double angle_step = (FOV * PI / 180.0) / NUM_RAYS;
    
//     mlx_clear_window(data->mlx, data->win_3d);
    
//     for (int i = 0; i < NUM_RAYS; i++) {
//         double ray_x = data->player.x;
//         double ray_y = data->player.y;
//         double ray_dir_x = cos(ray_angle);
//         double ray_dir_y = sin(ray_angle);
//         double distance = 0;
        
//         while (!is_wall(ray_x, ray_y)) {
//             ray_x += ray_dir_x;
//             ray_y += ray_dir_y;
//             distance += 1;
//             if (distance > 1000) break;
            
//             // Draw ALL rays in debug view (faint blue)
//             mlx_pixel_put(data->mlx, data->win_2d, (int)ray_x, (int)ray_y, 0x3333AA);
//         }
        
//         // Highlight the selected ray in yellow
//         // if (i == data->debug_ray_index) {
//         //     draw_line(data, data->player.x, data->player.y, ray_x, ray_y, YELLOW, 2);
            
//         //     // Print detailed angle info
//         //     printf("\n--- Ray %d ---\n", i);
//         //     printf("Absolute Angle: %.2f° (0°=right, 90°=up)\n", ray_angle * 180/PI);
//         //     printf("Relative to Player: %.2f°\n", 
//         //           (ray_angle - data->player.angle) * 180/PI);
//         //     printf("Hit at: (%.2f, %.2f)\n", ray_x, ray_y);
//         //     printf("Raw Distance: %.2f\n", distance);
//         //     printf("Corrected Distance: %.2f\n", 
//         //           distance * cos(ray_angle - data->player.angle));
//         // }
        
//         distance *= cos(ray_angle - data->player.angle);
//         draw_wall_slice(data, i, distance, i);
//         ray_angle += angle_step;
//     }
    
//     // Draw angle markers in debug view
//     char angle_text[50];
//     sprintf(angle_text, "Player Angle: %.1f°", data->player.angle * 180/PI);
//     mlx_string_put(data->mlx, data->win_2d, 10, 20, WHITE, angle_text);
// }


int handle_key(int key, t_data *data) {
    if (key == 65307) { // ESC
        mlx_destroy_window(data->mlx, data->win_3d);
        mlx_destroy_window(data->mlx, data->win_2d);
        exit(0);
    }
    
    // Movement
    if (key == 119) { // W
        data->player.x += cos(data->player.angle) * PLAYER_SPEED;
        data->player.y += sin(data->player.angle) * PLAYER_SPEED;
    }
    if (key == 115) { // S
        data->player.x -= cos(data->player.angle) * PLAYER_SPEED;
        data->player.y -= sin(data->player.angle) * PLAYER_SPEED;
    }
    if (key == 97) { // A
        data->player.x += sin(data->player.angle) * PLAYER_SPEED;
        data->player.y -= cos(data->player.angle) * PLAYER_SPEED;
    }
    if (key == 100) { // D
        data->player.x -= sin(data->player.angle) * PLAYER_SPEED;
        data->player.y += cos(data->player.angle) * PLAYER_SPEED;
    }
    
    // Rotation
    if (key == LEFT_ARROW)
	{
	 	data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
		
    if (key == RIGHT_ARROW){
		data->player.angle += ROTATION_SPEED; // Right
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}
    
    // Debug controls
    // if (key == 65451) data->debug_ray_index = (data->debug_ray_index + 1) % NUM_RAYS; // +
    // if (key == 65453) data->debug_ray_index = (data->debug_ray_index - 1 + NUM_RAYS) % NUM_RAYS; // -
    // if (key == 32) data->debug_ray_index = -1; // Space = show all rays
    
    // Update both views
    mlx_clear_window(data->mlx, data->win_2d);
    draw_map(data);
    cast_rays(data);
    
    return 0;
}

void    init_data(t_data *data)
{
    data->mlx = mlx_init();
    data->win_3d = mlx_new_window(data->mlx, NUM_RAYS, MAP_HEIGHT * TILE_SIZE, "3D View");
    data->win_2d = mlx_new_window(data->mlx, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "2D Debug View");
    
    data->player.x = TILE_SIZE * 3 + TILE_SIZE / 2;
    data->player.y = TILE_SIZE * 3 + TILE_SIZE / 2;
    data->player.angle = PI / 2;
    data->debug_ray_index = NUM_RAYS / 2;
    data->player.is_facing_down = 0;
    data->player.is_facing_up = 0;
    data->player.is_facing_right = 0;
    data->player.is_facing_left = 0;

    if (data->player.angle >= 0 && data->player.angle <= PI / 2)
        data->player.is_facing_down = 1;
    else
        data->player.is_facing_up = 1;
    if (data->player.angle >= PI / 2 && data->player.angle <= 1.5 * PI)
        data->player.is_facing_left = 1;
    else
        data->player.is_facing_right = 1;
}

int main(void) {
    t_data data;
    
    init_data(&data);
    draw_map(&data);
    cast_rays(&data);
    
    mlx_hook(data.win_3d, 2, 1L<<0, handle_key, &data);
    mlx_hook(data.win_2d, 2, 1L<<0, handle_key, &data);
    
    printf("Controls:\n");
    printf("WASD - Move\n");
    printf("Arrow keys - Rotate\n");
    printf("+/- - Select next/previous ray for debugging\n");
    printf("Space - Show all rays\n");
    
    mlx_loop(data.mlx);
    return 0;
}