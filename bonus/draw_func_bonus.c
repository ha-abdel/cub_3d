#include "cube_bonus.h"

void draw_square(t_data *data, int x, int y, int color, int win)
{
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
//             my_mlx_pixel_put(&data->bg1,  x0, y0, color);
//         else
//             my_mlx_pixel_put(&data->bg,  x0, y0, color);
//         if (x0 == x1 && y0 == y1) break;
//         e2 = err;
//         if (e2 > -dx) { err -= dy; x0 += sx; }
//         if (e2 < dy) { err += dx; y0 += sy; }
//     }
// }

void draw_line(t_data *data, t_point start_p, t_point end_p, int color, int win) 
{
    t_point point;
    double dx = end_p.x - start_p.x;
    double dy = end_p.y - start_p.y;
    double steps = fmax(fabs(dx),fabs(dy));
    steps = fmin(steps, data->max_dist_pixel);
    point.x = start_p.x;
    point.y = start_p.y;
    int i = 0;
    while (i < steps)
    {
        if (win == 1)
            my_mlx_pixel_put(&data->bg1, (int)point.x, (int)point.y, color);
        else
            my_mlx_pixel_put(&data->bg, (int)point.x, (int)point.y, color);
        i++;
        point.x+= dx / steps;
        point.y+= dy / steps;
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
            if (data->map.map[y][x] == 'D')
                draw_square(data, x * TILE_SIZE, y * TILE_SIZE, GREEN , 2);

            x++;
        }  
        y++;
    }
}

void    draw_grid_lines(t_data *data)
{
    int y = 0;
    int x = 0;
    t_point point1;
    t_point point2;

    while (x < data->map.width)
    {
        point1.x = x * TILE_SIZE;
        point1.y = 0;
        point2.x = x * TILE_SIZE;
        point2.y = data->map.height * TILE_SIZE;
        draw_line(data, point1, point2, GRAY, 2);
        x++;
    }
    while (y < data->map.height)
    {
        point1.x = 0;
        point1.y = y * TILE_SIZE;
        point2.x = data->map.width * TILE_SIZE;
        point2.y = y * TILE_SIZE;
        draw_line(data, point1, point2, GRAY, 2);
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
    t_point point1;
    t_point point2;
    int px = (int)data->player.x;
    int py = (int)data->player.y;

    int dx = px + cos(data->player.angle) * 30;
    int dy = py + sin(data->player.angle) * 30;

    point1.x = px;
    point1.y = py;
    point2.x = dx;
    point2.y = dy;
    
    draw_line(data, point1, point2, GREEN, 2);
}


void draw_map(t_data *data) {
    draw_walls(data);
    draw_grid_lines(data);
    draw_player(data);
    // draw_line(data, data->player.x, data->player.y, data->player.x + 50, data->player.y, WHITE, 2); // 0° reference (right)
    // draw_line(data, data->player.x, data->player.y, data->player.x, data->player.y + 50, WHITE, 2); // 90° reference (down)

}
