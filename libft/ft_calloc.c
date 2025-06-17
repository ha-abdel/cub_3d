/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:20:18 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 13:21:28 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int count, int size)
{
	int		len;
	void	*ptr;

	len = count * size;
	ptr = (void *)ft_malloc(len, 1);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}
