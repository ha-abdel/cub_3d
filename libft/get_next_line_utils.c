/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:42 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 15:51:48 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	if ((start) >= ft_strlen(s))
	{
		ptr = ft_strdup("");
		return (ptr);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	ptr = (char *)ft_malloc(len + 1, 1);
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
