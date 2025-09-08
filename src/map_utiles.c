/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:51:15 by salahian          #+#    #+#             */
/*   Updated: 2025/09/06 17:57:57 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_every_character(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != '1' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*get_new_line(char *str, int size)
{
	int		i;
	char	*tmp;

	tmp = ft_malloc(size + 1, 1);
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	while (i < size)
	{
		tmp[i] = ' ';
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	check_walls(t_data *data, int size)
{
	int	i;

	i = 1;
	if (!check_every_character(data->map.map[0])
		|| !check_every_character(data->map.map[size]))
		return (0);
	while (data->map.map[i])
	{
		if (data->map.map[i][0] != '1' && data->map.map[i][0] != ' ')
			return (0);
		if (data->map.map[i][data->map.width - 1] != '1'
			&& data->map.map[i][data->map.width - 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	calculate_lines(char *buf)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int	fill_map(char **map, char *line, int fd)
{
	int	i;

	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i] = ft_strdup(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (1);
}
