/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:31:11 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 13:23:09 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
