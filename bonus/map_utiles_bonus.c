/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utiles_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:25:31 by salahian          #+#    #+#             */
/*   Updated: 2025/09/08 09:23:02 by salahian         ###   ########.fr       */
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
		if (line[0] == '\0')
			return (0);
		map[i] = ft_strdup(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (1);
}
