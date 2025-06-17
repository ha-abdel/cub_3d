/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ha <abdel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:22:04 by abdel-ha          #+#    #+#             */
/*   Updated: 2024/11/05 12:09:14 by abdel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;
	t_list	*current;

	if (!lst || !del || !(*lst))
		return ;
	l = *lst;
	while (l)
	{
		current = l->next;
		del((l)->content);
		free(l);
		l = current;
	}
	*lst = NULL;
}
