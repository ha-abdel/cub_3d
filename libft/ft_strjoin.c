/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:27:51 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 13:22:46 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1len;
	int		s2len;
	int		totallen;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	totallen = s1len + s2len;
	ptr = (char *)ft_malloc(totallen + 1, 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, s1len);
	ft_memcpy(ptr + s1len, s2, s2len);
	ptr[totallen] = '\0';
	return (ptr);
}
