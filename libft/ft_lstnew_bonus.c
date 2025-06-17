/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:23:13 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/03/23 10:54:50 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = (t_list *)ft_malloc(sizeof(t_list), 1);
	if (!l)
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}
