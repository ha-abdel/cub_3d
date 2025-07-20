/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:28:13 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 16:24:50 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_perpendicular_to_yaxis(double ray_angle)
{
	if (ray_angle == 0 || ray_angle == PI)
		return (1);
	return (0);
}

int	is_perpendicular_to_xaxis(double ray_angle)
{
	if (ray_angle == 1.5 * PI || ray_angle == PI / 2)
		return (1);
	return (0);
}

void	normalize_angle(double *angle)
{
	(*angle) = fmod(*angle, 2 * PI);
	if (*angle < 0)
		(*angle) += 2 * PI;
}
