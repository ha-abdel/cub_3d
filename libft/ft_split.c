/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:26:10 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 13:22:30 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**free_split(char **arr, int i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
	return (NULL);
}

static char	*ft_checksep(char *s, char *sep, int *index)
{
	int		start;
	int		i;
	int		end;
	char	*ptr;

	start = *index;
	while (s[start] && ft_strchr(sep, s[start]))
		start++;
	end = start;
	while (s[end] && !ft_strchr(sep, s[end]))
		end++;
	*index = end;
	if (start >= end)
		return (NULL);
	ptr = (char *)ft_malloc(end - start + 1, 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (start < end)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

static int	ft_count_words(char *s, char *sep)
{
	int	count;
	int	i;
	int	inword;

	count = 0;
	i = 0;
	inword = 0;
	while (s[i])
	{
		if (!inword && !ft_strchr(sep, s[i]))
		{
			inword = 1;
			count++;
		}
		if (ft_strchr(sep, s[i]))
			inword = 0;
		i++;
	}
	return (count);
}

char	**ft_split(char *s, char *sep)
{
	int		i;
	char	**arr;
	int		index;

	if (!s)
		return (NULL);
	i = 0;
	index = ft_count_words(s, sep);
	arr = (char **)ft_malloc((index + 1) * sizeof(char *), 1);
	if (!arr)
		return (NULL);
	index = 0;
	while (i < ft_count_words(s, sep))
	{
		arr[i] = ft_checksep(s, sep, &index);
		if (!arr[i])
			return (free_split(arr, i));
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
