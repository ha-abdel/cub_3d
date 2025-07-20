#include "cube_bonus.h"

int is_perpendicular_to_yaxis(double ray_angle)
{
    if (ray_angle == 0 || ray_angle == PI)
        return 1;
    return 0;
}
int is_perpendicular_to_xaxis(double ray_angle)
{
    if (ray_angle == 1.5 * PI || ray_angle == PI / 2)
        return 1;
    return 0;
}

void    normalize_angle(double *angle)
{
    (*angle) = fmod(*angle, 2 * PI);
    if (*angle < 0)
        (*angle) += 2 * PI;
}