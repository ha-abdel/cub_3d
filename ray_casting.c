#include "cube.h"

// Modified map with player marker
// static char *g_map[] = {
//     "1111111111111111",
//     "1000000000000001",
//     "1000000000000001",
//     "10000000000N0001",
//     "1000001000000001",
//     "1000000000000001",
//     "1001000000000001",
//     "1000000000000001",
//     "1000001000000001",
//     "1000000000000001",
//     "1000000000000001",
//     "1111111111111111",
//     NULL
// };

//int is_wall(t_data *data, double x, double y) {
//    int grid_x = floor(x / TILE_SIZE);
//    int grid_y = floor(y / TILE_SIZE);
//    if (grid_x < 0 || grid_x >= data->map.width || grid_y < 0 || grid_y >= data->map.height || grid_x >= data->map.width || data->map.map[grid_y][grid_x] == '1')
//        return 1;
//    return (0);
//}





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

void check_horizontal_intersect(t_data *data, t_point *h_intersect, double ray_angle) {
    ray_angle = fmod(ray_angle, 2 * PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    // call function normalize angle

    if (is_perpendicular_to_Yaxis(ray_angle))
    {
        if (is_facing_right(ray_angle))
            (*h_intersect).x = data->player.x + 3000;
        else
            (*h_intersect).x = data->player.x - 3000;
        (*h_intersect).y = data->player.y;
        return;
    }
    double tan_val = tan(ray_angle);
    if (fabs(tan_val) <= 0.000001)
        tan_val = (tan_val >= 0) ? 0.000001 : -0.000001;

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
    (*h_intersect).x = first_x;
    (*h_intersect).y = first_y;

    while (!is_wall(data, (*h_intersect).x, (*h_intersect).y - is_facing_up(ray_angle)) && inside_bounds(data, (*h_intersect).x, (*h_intersect).y)) {
        (*h_intersect).x += x_step;
        (*h_intersect).y += y_step;
    }
}

void check_vertical_intersect(t_data *data, t_point *v_intersect, double ray_angle) {
    ray_angle = fmod(ray_angle, 2 * PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    // call function normalise angle 

    if (is_perpendicular_to_Xaxis(ray_angle))
    {
        (*v_intersect).x = data->player.x;
        if (is_facing_up(ray_angle))
            (*v_intersect).y = data->player.y + 3000;
        else
            (*v_intersect).y = data->player.y - 3000;
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
    (*v_intersect).x = first_x;
    (*v_intersect).y = first_y;
    while (!is_wall(data, (*v_intersect).x - is_facing_left(ray_angle), (*v_intersect).y) && inside_bounds(data, (*v_intersect).x, (*v_intersect).y)) {
        (*v_intersect).x += x_step;
        (*v_intersect).y += y_step;
    }
}

void cast_rays(t_data *data)
{
    double ray_angle = data->player.angle - (FOV / 2 * PI / 180.0);
    double angle_step = (FOV * PI / 180.0) / NUM_RAYS;
    double distance = 0;
    int i = 0;
    while( i < NUM_RAYS) {
        // double hx = -1; 
        // double hy = -1;
        // double vx = -1;
        // double vy = -1;
        t_point h_intersect;
        t_point v_intersect;
        int color;
        t_point player;
        player.x = data->player.x;
        player.y = data->player.y;
        t_point ray_end;
        check_horizontal_intersect(data, &h_intersect, ray_angle);
        check_vertical_intersect(data, &v_intersect, ray_angle);
        double h_dist = (h_intersect.x - data->player.x) * (h_intersect.x - data->player.x) + (h_intersect.y - data->player.y) * (h_intersect.y - data->player.y);
        double v_dist = (v_intersect.x - data->player.x) * (v_intersect.x - data->player.x) + (v_intersect.y - data->player.y) * (v_intersect.y - data->player.y);
                
        // if(i == 0 || i == NUM_RAYS - 1 || i == NUM_RAYS /2)
        // {
        // printf(" Ray %d\n",i);
        // printf("hdist : %0.2f\nvdist : %0.2f\n",sqrt(h_dist),sqrt(v_dist));
        // ft_player_debug(data);
        // }
      

        if (h_dist < v_dist) {
            color = RED;
            distance = sqrt(h_dist);
            ray_end.x = h_intersect.x;
            ray_end.y = h_intersect.y;
        } else {
            color = BLUE;
            distance = sqrt(v_dist);
            ray_end.x = v_intersect.x;
            ray_end.y = v_intersect.y;
        }
        distance *= cos(ray_angle - data->player.angle);
        draw_line(data, player, ray_end, BLUE, 2);
        double dist_projection_plane = (screen_width / 2.0) / tan ((FOV / 2.0) * PI / 180);
        double wall_strip = (TILE_SIZE / distance) * dist_projection_plane ;

        int wall_top = (screen_height) / 2 - wall_strip / 2;
        int wall_bottom = wall_top + wall_strip;
        if (wall_top < 0)
            wall_top = 0;
        if (wall_bottom > screen_height)
            wall_bottom = screen_height;

        t_point point1;
        t_point point2;
        point1.x = i;
        point1.y = wall_top;
        point2.x = i;
        point2.y = wall_bottom;
        draw_line(data, point1, point2, color, 1);
        // printf("start of line %d\n", wall_top);
        // printf("end of line %d\n", wall_bottom);
        ray_angle += angle_step;
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
