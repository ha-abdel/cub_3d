#include "cube_bonus.h"

void	print_info(t_data *data)
{
	int	i;

	i = 0;
	while (data->doors[i])
	{
		printf("door id is %d\n", i + 1);
		printf("door col is %d\n", data->doors[i]->col);
		printf("door row is %d\n", data->doors[i]->row);
		printf("door is open %s\n", data->doors[i]->open ? "true" : "false");
		i++;
	}
}

void	print_hit_info(t_data *data)
{
	printf("door hit horizontally %d\n", data->hit.is_h_door);
	printf("door hit vertically %d\n", data->hit.is_v_door);
	printf("wall hit horizontally %d\n", data->hit.is_h_wall);
	printf("wall hit vertically %d\n", data->hit.is_v_wall);
	printf("final hit door %d\n", data->hit.is_door);
	printf("final hit wall %d\n", data->hit.is_wall);
	printf("h dist %f\n", data->hit.h_dist);
	printf("v dist %f\n", data->hit.v_dist);
}

void	print_front_doors(t_data *data)
{
	int i = 0;
	while (i < data->nb_doors)
	{
		printf("door %d is %s\n", i, data->front_doors[i] == 1 ? "opend" : "closed");
		i++;
	}
	printf("===================\n");
}