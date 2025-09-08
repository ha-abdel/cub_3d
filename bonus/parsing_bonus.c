/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:15:15 by salahian          #+#    #+#             */
/*   Updated: 2025/09/06 15:40:31 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	take_color(t_data *data, char *line, char *s, int index)
{
	char	*tmp;
	int		count;

	tmp = NULL;
	count = 0;
	while (line[index])
	{
		if (!parse_spaces(line, &index, 1))
			return (0);
		if (line[index] == ',')
		{
			index++;
			count++;
			if (!parse_spaces(line, &index, 0))
				return (0);
			if (!fill_color(data, s, tmp, count))
				return (0);
			tmp = NULL;
		}
		tmp = ft_strjoin(tmp, append_char(line[index]));
		index++;
	}
	return (help_fill_data(data, tmp, s, &count));
}

int	check_parameters(t_data *data, char **tmp, char *line)
{
	int		i;
	char	*str;
	char	*s;

	if (line[0] == '\n')
		return (1);
	i = 0;
	str = NULL;
	s = NULL;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && (line[i] >= 'A' && line[i] <= 'Z'))
	{
		str = ft_strjoin(str, append_char(line[i]));
		i++;
	}
	if (line[i] && (line[i] != ' ' && line[i] != '\t'))
		return (0);
	if (!check_is_valid_param(tmp, str, &s))
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || !fill_data(data, line, s, i))
		return (0);
	return (1);
}

int	read_file(t_data *data, char *file)
{
	int		fd;
	char	*line;
	char	**tmp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	tmp = ft_malloc(sizeof(char *) * 7, 1);
	fill_tmp(tmp);
	while (line)
	{
		if (check_is_map(line))
		{
			if (!check_data(data))
				return (0);
			return (map_check(data, file, line, fd));
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] && !check_parameters(data, tmp, line))
			return (close(fd), 0);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

int	check_name(char *file)
{
	int	slash;

	slash = get_last_slash(file);
	if (slash == -1)
	{
		if (ft_strlen(file) <= 4)
			return (0);
		if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4) != 0)
			return (0);
	}
	else
	{
		if (ft_strlen(&file[slash + 1]) <= 4)
			return (0);
		if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4) != 0)
			return (0);
	}
	return (1);
}

// void	print_map(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i])
// 	{
// 		printf("[%s]\n", map[i]);
// 		i++;
// 	}
// }

// void	print_data(t_data *data)
// {
// 	printf("path_s:[%s]\n", data->map.s_path);
// 	printf("path_n:[%s]\n", data->map.n_path);
// 	printf("path_w:[%s]\n", data->map.w_path);
// 	printf("path_e:[%s]\n", data->map.e_path);
// 	printf("angle:[%f]\n", data->player.angle);
// 	printf("color_c:[%d]\n", data->map.c_color);
// 	printf("color_f:[%d]\n", data->map.f_color);
// 	printf("height:[%d]\n", data->map.height);
// 	printf("width:[%d]\n", data->map.width);
// 	printf("pos.x:[%f]\n", data->player.x);
// 	printf("pos.y:[%f]\n", data->player.y);
// 	print_map(data->map.map);
// }

int	main_function_parsing(t_data *data, char *file)
{
	if (!check_name(file))
	{
		printf("Error\nNAME\n");
		return (0);
	}
	if (!read_file(data, file) || !check_data(data))
	{
		return (printf("Error\nFILE\n"), 0);
	}
	if (!data->map.map)
	{
		printf("Error\nMAP\n");
		return (0);
	}
	return (1);
}
