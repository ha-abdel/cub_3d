/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salahian <salahian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:39:36 by salahian          #+#    #+#             */
/*   Updated: 2025/09/06 14:44:21 by salahian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	fill_tmp(char **tmp)
{
	tmp[0] = ft_strdup("NO");
	tmp[1] = ft_strdup("SO");
	tmp[2] = ft_strdup("WE");
	tmp[3] = ft_strdup("EA");
	tmp[4] = ft_strdup("F");
	tmp[5] = ft_strdup("C");
	tmp[6] = NULL;
}

char	*append_char(char c)
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

int	fill_color(t_data *data, char *s, char *tmp, int count)
{
	int	nbr;
	int	flag;

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

int	help_fill_data(t_data *data, char *tmp, char *s, int *count)
{
	if (tmp)
	{
		(*count)++;
		if (!fill_color(data, s, tmp, *count))
			return (0);
	}
	if (*count != 3)
		return (0);
	return (1);
}
