/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:51:46 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/07/20 15:38:56 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	copy_img(t_sprite *src, t_sprite **dst)
{
	(*dst)->addr = src->addr;
	(*dst)->width = src->width;
	(*dst)->height = src->height;
	(*dst)->bpp = src->bpp;
	(*dst)->line_len = src->line_len;
	(*dst)->img = src->img;
}
void	get_texture_img(t_data *data, t_ray *ray, t_sprite *img)
{
	set_wall_type(ray);
	if (ray->wall_type == N_WALL)
		copy_img(&data->n_wall, &img);
	else if (ray->wall_type == S_WALL)
		copy_img(&data->s_wall, &img);
	else if (ray->wall_type == E_WALL)
		copy_img(&data->e_wall, &img);
	else if (ray->wall_type == W_WALL)
		copy_img(&data->w_wall, &img);
}

void	set_wall_type(t_ray *ray)
{
	if (ray->h_dist <= ray->v_dist)
	{
		if (is_facing_down(ray->ray_angle))
			ray->wall_type = N_WALL;
		else
			ray->wall_type = S_WALL;
	}
	else if (ray->h_dist > ray->v_dist)
	{
		if (is_facing_right(ray->ray_angle))
			ray->wall_type = E_WALL;
		else
			ray->wall_type = W_WALL;
	}
}