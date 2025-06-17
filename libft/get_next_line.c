/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:23 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/05/16 18:31:40 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

char	*fill_line(char **leftover)
{
	char	*line;
	char	*new_leftover;
	int		i;

	if (!*leftover || **leftover == '\0')
		return (NULL);
	i = 0;
	while ((*leftover)[i] && (*leftover)[i] != '\n')
		i++;
	if ((*leftover)[i] == '\n')
		line = ft_substr(*leftover, 0, i + 1);
	else
		line = ft_substr(*leftover, 0, i);
	if (!line)
		return (NULL);
	if ((*leftover)[i] == '\n')
		new_leftover = ft_strdup(*leftover + i + 1);
	else
		new_leftover = NULL;
	if ((*leftover)[i] == '\n' && !new_leftover)
		return (NULL);
	*leftover = new_leftover;
	return (line);
}

char	*read_data_from_buffer(char **leftover, int fd)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*leftover, buffer);
		if (!temp)
			return (NULL);
		*leftover = temp;
		if (ft_strchr(buffer, '\n'))
			return (fill_line(leftover));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0 || (!*leftover))
		return (NULL);
	if (bytes_read < 0 || **leftover == '\0')
		return (NULL);
	return (fill_line(leftover));
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (leftover && ft_strchr(leftover, '\n'))
		return (fill_line(&leftover));
	if (!leftover)
		leftover = ft_strdup("");
	if (!leftover)
		return (NULL);
	line = read_data_from_buffer(&leftover, fd);
	if (!line && leftover && *leftover)
	{
		line = ft_strdup(leftover);
	}
	if (!line && (!leftover || *leftover == '\0'))
		return (NULL);
	return (line);
}
