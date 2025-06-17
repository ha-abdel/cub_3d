/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:24:54 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/07 13:52:48 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, int len)
{
	int				i;
	unsigned char	value;
	unsigned char	*ptr;

	i = 0;
	value = (unsigned char)c;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = value;
		i++;
	}
	return (b);
}
