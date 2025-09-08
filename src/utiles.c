/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:14:51 by salahian          #+#    #+#             */
/*   Updated: 2025/09/07 15:45:46 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	handle_direction(t_data *data, char c, int i, int j)
{
	if ((c != 'N' && c != 'E' && c != 'W' && c != 'S')
		|| (data->player.angle != -1))
		return (0);
	if (c == 'N')
		data->player.angle = PI / 2;
	if (c == 'E')
		data->player.angle = 0;
	if (c == 'W')
		data->player.angle = PI;
	if (c == 'S')
		data->player.angle = 1.5 * PI;
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
