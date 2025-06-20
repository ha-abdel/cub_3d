

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TILE_SIZE 64
#define FOV 60.0
#define NUM_RAYS 800
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


void draw_map(t_data *data) {
    // Draw grid and walls (same as before)
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 
                       g_map[y][x] == '1' ? DARK_GRAY : BLACK, 2);
        }
    }
    
    // Draw grid lines
    for (int x = 0; x <= MAP_WIDTH; x++) {
        draw_line(data, x * TILE_SIZE, 0, x * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, GRAY, 2);
    }
    for (int y = 0; y <= MAP_HEIGHT; y++) {
        draw_line(data, 0, y * TILE_SIZE, MAP_WIDTH * TILE_SIZE, y * TILE_SIZE, GRAY, 2);
    }
    
    // Draw player position (center marker)
    int px = (int)data->player.x;
    int py = (int)data->player.y;
    
    // Draw player as a red circle with direction indicator
    for (int dy = -5; dy <= 5; dy++) {
        for (int dx = -5; dx <= 5; dx++) {
            if (dx*dx + dy*dy <= 25) // Circle equation
                mlx_pixel_put(data->mlx, data->win_2d, px+dx, py+dy, RED);
        }
    }
    
    // Draw direction line (longer for better visibility)
    int dx = px + cos(data->player.angle) * 30;
    int dy = py + sin(data->player.angle) * 30;
    draw_line(data, px, py, dx, dy, GREEN, 2);
    
    // Draw angle reference lines (0° and 90°)
    draw_line(data, px, py, px + 50, py, WHITE, 2); // 0° reference (right)
    draw_line(data, px, py, px, py + 50, WHITE, 2); // 90° reference (down)
}

void cast_rays(t_data *data) {
    double ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    double angle_step = (FOV * PI / 180.0) / NUM_RAYS;
    
    mlx_clear_window(data->mlx, data->win_3d);
    
    for (int i = 0; i < NUM_RAYS; i++) {
        double ray_x = data->player.x;
        double ray_y = data->player.y;
        double ray_dir_x = cos(ray_angle);
        double ray_dir_y = sin(ray_angle);
        double distance = 0;
        
        while (!is_wall(ray_x, ray_y)) {
            ray_x += ray_dir_x;
            ray_y += ray_dir_y;
            distance += 1;
            if (distance > 1000) break;
            
            // Draw ALL rays in debug view (faint blue)
            mlx_pixel_put(data->mlx, data->win_2d, (int)ray_x, (int)ray_y, 0x3333AA);
        }
        
        // Highlight the selected ray in yellow
        // if (i == data->debug_ray_index) {
        //     draw_line(data, data->player.x, data->player.y, ray_x, ray_y, YELLOW, 2);
            
        //     // Print detailed angle info
        //     printf("\n--- Ray %d ---\n", i);
        //     printf("Absolute Angle: %.2f° (0°=right, 90°=up)\n", ray_angle * 180/PI);
        //     printf("Relative to Player: %.2f°\n", 
        //           (ray_angle - data->player.angle) * 180/PI);
        //     printf("Hit at: (%.2f, %.2f)\n", ray_x, ray_y);
        //     printf("Raw Distance: %.2f\n", distance);
        //     printf("Corrected Distance: %.2f\n", 
        //           distance * cos(ray_angle - data->player.angle));
        // }
        
        distance *= cos(ray_angle - data->player.angle);
        draw_wall_slice(data, i, distance, i);
        ray_angle += angle_step;
    }
    
    // Draw angle markers in debug view
    char angle_text[50];
    sprintf(angle_text, "Player Angle: %.1f°", data->player.angle * 180/PI);
    mlx_string_put(data->mlx, data->win_2d, 10, 20, WHITE, angle_text);
}


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
    if (key == 65361)
	{
	 	data->player.angle -= ROTATION_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
		
    if (key == 65363){
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

int main(void) {
    t_data data;
    
    data.mlx = mlx_init();
    data.win_3d = mlx_new_window(data.mlx, NUM_RAYS, MAP_HEIGHT * TILE_SIZE, "3D View");
    data.win_2d = mlx_new_window(data.mlx, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "2D Debug View");
    
    data.player.x = TILE_SIZE * 3 + TILE_SIZE / 2;
    data.player.y = TILE_SIZE * 3 + TILE_SIZE / 2;
    data.player.angle = PI / 2;
    data.debug_ray_index = NUM_RAYS / 2; // Start with center ray
    
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