/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:23:16 by salahian          #+#    #+#             */
/*   Updated: 2025/07/09 15:13:57 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void mdraw_square(t_sprite *img, int x, int y, int color, int radius) {
    for (int dy = 0; dy < TILE_SIZE; dy++) {
        for (int dx = 0; dx < TILE_SIZE; dx++) {
                	my_mlx_pixel(img, x + dx, y + dy, color);
        }
    }
}

//void mdraw_minimap_walls(t_data *data, t_sprite *img, int cx, int cy, int radius)
//{
//    int x, y;
//    int tile_cx, tile_cy;
//    int dx, dy;
//    int r2 = radius * radius;

//    for (y = 0; y < data->map.height; y++)
//    {
//        for (x = 0; x < data->map.width; x++)
//        {
//            tile_cx = cx + (x - data->player.x / TILE_SIZE) * TILE_SIZE;
//            tile_cy = cy + (y - data->player.y / TILE_SIZE) * TILE_SIZE;

//            dx = tile_cx - cx;
//            dy = tile_cy - cy;

//            if (dx * dx + dy * dy <= r2)
//            {
//                int color = (data->map.map[y][x] == '1') ? RED : DARK_GRAY;
//                mdraw_square(img, tile_cx, tile_cy, color, radius);
//            }
//        }
//    }
//}

void mdraw_minimap_walls(t_data *data, t_sprite *img, int cx, int cy, int radius)
{
    int x, y;
    int px, py;
    int r2 = radius * radius;

    for (y = 0; y < data->map.height; y++)
    {
        for (x = 0; x < data->map.width; x++)
        {
            int tile_start_x = cx + (x - data->player.x / TILE_SIZE) * TILE_SIZE;
            int tile_start_y = cy + (y - data->player.y / TILE_SIZE) * TILE_SIZE;

            int color = (data->map.map[y][x] == '1') ? RED : DARK_GRAY;

            for (int dy = 0; dy < TILE_SIZE; dy++)
            {
                for (int dx = 0; dx < TILE_SIZE; dx++)
                {
                    px = tile_start_x + dx;
                    py = tile_start_y + dy;
                    int dist2 = (px - cx) * (px - cx) + (py - cy) * (py - cy);

                    if (dist2 <= r2)
                        my_mlx_pixel(img, px, py, color);
                }
            }
        }
    }
}



void draw_circle(t_data *data, int cx, int cy, int radius)
{
    int x;
	int	y;
    int r2;
    int thickness;
	int dist2;

	thickness = 150;
	r2 = radius * radius;
	y = -radius;
    while (y <= radius)
    {
		x = -radius;
        while (x <= radius)
        {
            dist2 = x * x + y * y;
            if (dist2 >= r2 - thickness && dist2 <= r2 + thickness)
                my_mlx_pixel(&data->bg1, cx + x, cy + y, WHITE);
            //else if (dist2 <= r2 - thickness)
                //mdraw_map(data, img, cx + x, cy + y);
			x++;
        }
		y++;
    }
}

void drawline(t_data *data, int x0, int y0, int x1, int y1, int color, int win) {
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
        my_mlx_pixel(&data->bg1, (int)x, (int)y, color);
        i++;
        x+= inc_x;
        y+= inc_y;
    }
}

void    draw_directionlines(t_data *data)
{
    int px = NUM_RAYS - 150;
    int py = data->map.height * TILE_SIZE - 150;

    int dx = px + cos(data->player.angle) * 30;
    int dy = py + sin(data->player.angle) * 30;
    
    drawline(data, px, py, dx, dy, GREEN, 2);
}

void	create_minimap(t_data *data)
{

	draw_circle(data, NUM_RAYS - 150, data->map.height * TILE_SIZE - 150, 130);
	mdraw_minimap_walls(data, &data->bg1, NUM_RAYS - 150, data->map.height * TILE_SIZE - 150, 130);
    draw_circle(data, NUM_RAYS - 150, data->map.height * TILE_SIZE - 150, 3);
	draw_directionlines(data);
	
}