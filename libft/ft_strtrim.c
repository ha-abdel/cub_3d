/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:30:02 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 13:23:00 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (j > i && ft_strchr(set, s1[j - 1]) != NULL)
		j--;
	ptr = (char *)ft_malloc((j - i) + 1, 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + i, (j - i) + 1);
	return (ptr);
}
