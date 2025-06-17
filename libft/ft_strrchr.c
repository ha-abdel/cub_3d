/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:29:41 by abdel-ha          #+#    #+#             */
/*   Updated: 2024/11/06 10:25:52 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int				i;
	unsigned char	tofind;

	i = ft_strlen(s);
	tofind = (unsigned char)c;
	if (tofind == '\0')
		return ((char *)(s + i));
	while (i--)
	{
		if (s[i] == tofind)
			return ((char *)(s + i));
	}
	return (NULL);
}
