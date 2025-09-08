/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:11:04 by salahian          #+#    #+#             */
/*   Updated: 2025/09/06 17:57:57 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	take_path(t_data *data, char *line, char *s, int index)
{
	if (s[0] == 'N')
		data->map.n_path = ft_strdup(&line[index]);
	else if (s[0] == 'E')
		data->map.e_path = ft_strdup(&line[index]);
	else if (s[0] == 'W')
		data->map.w_path = ft_strdup(&line[index]);
	else if (s[0] == 'S')
		data->map.s_path = ft_strdup(&line[index]);
	data->map.direction++;
}

int	fill_data(t_data *data, char *line, char *s, int index)
{
	if (ft_isdigit(line[index]))
	{
		if (!take_color(data, line, s, index))
			return (0);
		return (1);
	}
	else
		take_path(data, line, s, index);
	return (1);
}

int	check_is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		return (1);
	return (0);
}

int	check_data(t_data *data)
{
	if (data->map.c_color == -1 || data->map.f_color == -1
		|| data->map.direction != 4)
		return (0);
	return (1);
}

int	get_last_slash(char *file)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (file[i])
	{
		if (file[i] == '/')
			last = i;
		i++;
	}
	return (last);
}
