/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:38:29 by salahian          #+#    #+#             */
/*   Updated: 2025/09/06 15:44:58 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

unsigned int	get_color(t_sprite *img, int x, int y)
{
	unsigned int	color;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (BLACK);
	color = *(unsigned int *)(img->addr + (y * img->line_len + x * (img->bpp
					/ 8)));
	return (color);
}

int	handle_direction(t_data *data, char c, int i, int j)
{
	if ((c != 'N' && c != 'E' && c != 'W' && c != 'S' && c != 'D' && c != 'P')
		|| (data->player.angle != -1 && (c != 'D' && c != 'P')))
		return (0);
	if (c == 'N')
		data->player.angle = PI / 2;
	if (c == 'E')
		data->player.angle = 0;
	if (c == 'W')
		data->player.angle = PI;
	if (c == 'S')
		data->player.angle = 1.5 * PI;
	if (c == 'D' || c == 'P')
	{
		if (data->map.map[i + 1][j] == '0' || data->map.map[i - 1][j] == '0')
		{
			if (data->map.map[i][j + 1] == '0' || data->map.map[i][j
				- 1] == '0')
				return (0);
		}
		return (1);
	}
	data->player.y = i;
	data->player.x = j;
	return (1);
}

int	check_is_valid_param(char **tmp, char *str, char **s)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (ft_strncmp(str, tmp[i], ft_strlen(str)) == 0)
		{
			tmp[i] = "\0";
			*s = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_spaces(char *line, int *index, int flag)
{
	if (flag && (!ft_isdigit(line[*index]) && line[*index] != ','))
	{
		if (line[*index] == ' ')
		{
			while (line && line[*index] == ' ')
				(*index)++;
		}
		else
			return (0);
	}
	else if (!flag && !ft_isdigit(line[*index]))
	{
		if (line[*index] == ' ')
		{
			while (line && line[*index] == ' ')
				(*index)++;
		}
		else
			return (0);
	}
	return (1);
}
