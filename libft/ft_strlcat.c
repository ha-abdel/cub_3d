/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:28:02 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/10 09:46:15 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, char *src, int dstsize)
{
	int	i;
	int	srclen;
	int	dstlen;
	int	j;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	j = dstlen;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	while (src[i] && j < dstsize - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (srclen + dstlen);
}
