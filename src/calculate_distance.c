#include "../cube.h"

void	calc_distance(t_data *data, t_ray *ray, int *color)
{
	ray->h_dist = (ray->h_intersect.x - data->player.x) * (ray->h_intersect.x
			- data->player.x) + (ray->h_intersect.y - data->player.y)
		* (ray->h_intersect.y - data->player.y);
	ray->v_dist = (ray->v_intersect.x - data->player.x) * (ray->v_intersect.x
			- data->player.x) + (ray->v_intersect.y - data->player.y)
		* (ray->v_intersect.y - data->player.y);

	if (ray->h_dist < ray->v_dist)
	{
		*color = 0xaa0000;
		ray->distance = sqrt(ray->h_dist);
		ray->ray_end.x = ray->h_intersect.x;
		ray->ray_end.y = ray->h_intersect.y;
	}
	else
	{
		*color = 0xff0000;
		ray->distance = sqrt(ray->v_dist);
		ray->ray_end.x = ray->v_intersect.x;
		ray->ray_end.y = ray->v_intersect.y;
	}
	ray->distance *= cos(ray->ray_angle - data->player.angle);
	draw_line(data, ray->player, ray->ray_end, BLUE, 2);
}
