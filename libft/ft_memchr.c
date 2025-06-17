/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:23:49 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/10 12:20:22 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, int n)
{
	int				i;
	unsigned char	tofind;
	unsigned char	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	tofind = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == tofind)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
