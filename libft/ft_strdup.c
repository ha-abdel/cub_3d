/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:27:18 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 13:22:41 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	int		len;
	char	*result;

	len = ft_strlen(s1) + 1;
	result = (char *)ft_malloc(len, 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len);
	return (result);
}
