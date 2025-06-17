/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:24:44 by abdel-ha          #+#    #+#             */
/*   Updated: 2024/11/06 10:20:44 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, int len)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = (unsigned char *)dst;
	s = (unsigned const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		ft_memcpy(dst, src, len);
		return (dst);
	}
	while (len--)
	{
		d[len] = s[len];
	}
	return (dst);
}
