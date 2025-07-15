#include "../cube.h"

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