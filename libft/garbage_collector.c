/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:31:28 by abdel-ha          #+#    #+#             */
/*   Updated: 2025/05/16 18:31:29 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(t_allocs **lst)
{
	t_allocs	*l;
	t_allocs	*current;

	if (!lst || !(*lst))
		return ;
	l = *lst;
	while (l)
	{
		current = l->next;
		free((l)->ptr);
		free(l);
		l = current;
	}
	*lst = NULL;
}

void	*ft_malloc(size_t size, int flag)
{
	static t_allocs	*allocations = NULL;
	t_allocs		*new;

	if (!flag)
		return (ft_free(&allocations), NULL);
	new = malloc(sizeof(t_allocs));
	new->ptr = malloc(size);
	if (!(new->ptr))
		return (NULL);
	ft_memset(new->ptr, 0, size);
	new->next = allocations;
	allocations = new;
	return (new->ptr);
}
