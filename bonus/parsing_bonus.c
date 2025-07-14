/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:15:15 by salahian          #+#    #+#             */
/*   Updated: 2025/07/14 16:57:53 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	fill_tmp(char **tmp)
{
	tmp[0] = ft_strdup("NO");
	tmp[1] = ft_strdup("SO");
	tmp[2] = ft_strdup("WE");
	tmp[3] = ft_strdup("EA");
	//tmp[4] = ft_strdup("N");
	//tmp[5] = ft_strdup("S");
	//tmp[6] = ft_strdup("W");
	//tmp[7] = ft_strdup("E");
	tmp[4] = ft_strdup("F");
	tmp[5] = ft_strdup("C");
	tmp[6] = NULL;
}

int		check_is_valid_param(char **tmp, char *str, char **s)
{
	int		i;

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

char *append_char(char c)
{
	char	*tmp;

	tmp = ft_malloc(2, 1);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}

void	set_color(int *color, int nbr, int count)
{
	if (count == 1)
		*color = (*color & 0x00FFFF) | (nbr << 16);
	else if (count == 2)
		*color = (*color & 0xFF00FF) | (nbr << 8);
	else
		*color = (*color & 0xFFFF00) | (nbr);
}

int		fill_color(t_data *data, char *s, char *tmp, int count)
{
	int		nbr;
	int		flag;

	flag = 0;
	nbr = 0;
	nbr = ft_atoi(tmp, &flag);
	if (flag || nbr > 255)
		return (0);
	if (*s == 'F')
		set_color(&data->map.f_color, nbr, count);
	else
		set_color(&data->map.c_color, nbr, count);
	return (1);
}

int		fill_data(t_data *data, char *line, char *s, int index)
{
	char	*tmp;
	int		count;
	
	tmp = NULL;
	if (ft_isdigit(line[index]))
	{
		count = 0;
		while (line[index])
		{
			if (!ft_isdigit(line[index]) && line[index] != ',')
				return (0);
			if (line[index] == ',')
			{
				index++;
				count++;
				if (!ft_isdigit(line[index]))
					return (0);
				if (!fill_color(data, s, tmp, count))
					return (0);
				tmp = NULL;
			}
			tmp = ft_strjoin(tmp, append_char(line[index]));
			index++;
		}
		if (tmp)
		{
			count++;
			if (!fill_color(data, s, tmp, count))
				return (0);
		}
		if (count != 3)
			return (0);
	}
	else
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
	return (1);
}

int		check_parameters(t_data *data, char **tmp, char *line)
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

int		check_line(t_data *data, char **tmp, char *line)
{
	if (!check_parameters(data, tmp, line))
		return (0);
	return (1);
}

int		check_is_map(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
			return (1);
	return (0);
}

int		check_data(t_data *data)
{
	if (data->map.c_color == -1 || data->map.f_color == -1 || data->map.direction != 4)
		return (0);
	return (1);
}

int		read_file(t_data *data, char *file)
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
		if (line[0] && !check_line(data, tmp, line))
		{
			close(fd);
			return (0);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int		get_last_slash(char *file)
{
	int		i;
	int		last;

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

int		check_name(char *file)
{
	int		slash;

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

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("[%s]\n", map[i]);
		i++;
	}
}

void	print_data(t_data *data)
{
	printf("path_s:[%s]\n", data->map.s_path);
	printf("path_n:[%s]\n", data->map.n_path);
	printf("path_w:[%s]\n", data->map.w_path);
	printf("path_e:[%s]\n", data->map.e_path);
	printf("angle:[%f]\n", data->player.angle);
	printf("color_c:[%d]\n", data->map.c_color);
	printf("color_f:[%d]\n", data->map.f_color);
	printf("height:[%d]\n", data->map.height);
	printf("width:[%d]\n", data->map.width);
	printf("pos.x:[%f]\n", data->player.x);
	printf("pos.y:[%f]\n", data->player.y);
	print_map(data->map.map);
}

int		main_function_parsing(t_data *data, char *file)
{
	if (!check_name(file))
	{
		printf("\nError\n NAME\n");
		return (0);
	}
	if (!read_file(data, file) || !check_data(data))
	{
		printf("\nError\n FILE\n");
		return (0);
	}
	if (!data->map.map)
	{
		printf("\nError\n MAP\n");
		return (0);
	}
	// print_data(data);
	printf("\nSUCCESS\n");
	return (1);
	//return (info);
}

// n = 90
// e = 0
// w = 180
// s = 270