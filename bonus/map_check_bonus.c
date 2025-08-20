/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:06:27 by salahian          #+#    #+#             */
/*   Updated: 2025/08/19 16:21:47 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	get_long_line(char **map)
{
	int	i;
	int	j;
	int	line;

	i = 0;
	line = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > line)
			line = j;
		i++;
	}
	line++;
	return (line);
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

int	handle_direction(t_data *data, char c, int i, int j)
{
	if ((c != 'N' && c != 'E' && c != 'W' && c != 'S' && c != 'D') || (data->player.angle != -1 && c != 'D'))
		return (0);
	if (c == 'N')
		data->player.angle = PI / 2;
	if (c == 'E')
		data->player.angle = 0;
	if (c == 'W')
		data->player.angle = PI;
	if (c == 'S')
		data->player.angle = 1.5 * PI;
	if (c == 'D')
	{
		if (data->map.map[i + 1][j] == '0' || data->map.map[i - 1][j] == '0')
		{
			if (data->map.map[i][j + 1] == '0' || data->map.map[i][j - 1] == '0')
				return (0);
		}
	}
	if (c != 'D')
	{
		data->player.y = i;
		data->player.x = j;
	}
	return (1);
}

int	check_around_floor(t_data *data, int i, int j)
{
	if (j != 0)
	{
		if (data->map.map[i][j - 1] == ' ')
			return (0);
	}
	if (j != data->map.width - 1)
	{
		if (data->map.map[i][j + 1] == ' ')
			return (0);
	}
	if (i != 0)
	{
		if (data->map.map[i - 1][j] == ' ')
			return (0);
	}
	if (i != data->map.height - 1)
	{
		if (data->map.map[i + 1][j] == ' ')
			return (0);
	}	
	return (1);
}

int	valid_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (!ft_isdigit(data->map.map[i][j]) && data->map.map[i][j] != ' ')
			{
				if (!handle_direction(data, data->map.map[i][j], i, j))
					return (0);
			}
			if (data->map.map[i][j] == '0')
			{
				if (!check_around_floor(data, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		check_every_character(char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != '1' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		check_walls(t_data *data, int size)
{
	int		i;

	i = 1;
	if (!check_every_character(data->map.map[0]) || !check_every_character(data->map.map[size]))
		return (0);
	while (data->map.map[i])
	{
		if (data->map.map[i][0] != '1' && data->map.map[i][0] != ' ')
			return (0);
		if (data->map.map[i][data->map.width - 1] != '1' && data->map.map[i][data->map.width - 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	create_new_map(t_data *data, char **map, int size)
{
	int	i;
	int	long_line;

	data->map.map = ft_malloc(sizeof(char *) * (size + 1), 1);
	long_line = get_long_line(map) - 1;
	i = 0;
	while (map[i])
	{
		if (long_line > ft_strlen(map[i]))
			data->map.map[i] = get_new_line(map[i], long_line);
		else
			data->map.map[i] = ft_strdup(map[i]);
		i++;
	}
	data->map.map[i] = NULL;
	data->map.height = size;
	data->map.width = long_line;
	if (!check_walls(data, size) || !valid_map(data))
		return (0);
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
		// if (line[0] == '\0')
		// {
		// 	printf("here\n");
		// 	return (0);
		// }
		map[i] = ft_strdup(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (1);
}

int	map_check(t_data *data, char *file, char *line, int fd)
{
	char	*buf;
	char	**map;
	int		count;
	int		flag;
	char	*n_line;

	buf = ft_malloc(1025, 1);
	count = 1;
	flag = 1;
	n_line = get_next_line(fd);
	while (n_line)
	{
		count++;
		n_line = get_next_line(fd);
	}
	close(fd);
	map = ft_malloc(sizeof(char *) * (count + 1), 1);
	fd = open(file, O_RDONLY);
	n_line = get_next_line(fd);
	while (ft_strncmp(n_line, line, ft_strlen(line)) != 0)
		n_line = get_next_line(fd);
	if (!fill_map(map, n_line, fd) || !create_new_map(data, map, count))
		return (0);
	return (1);
}
