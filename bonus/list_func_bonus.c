#include "cube_bonus.h"

t_door	*ft_lstnew1(void)
{
	t_door	*l;

	l = (t_door *)ft_malloc(sizeof(t_door), 1);
	if (!l)
		return (NULL);
	l->next = NULL;
	l->prev = NULL;
	return (l);
}

t_door	*ft_lstlast1(t_door *lst)
{
	t_door	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

// void	ft_lstadd_front1(t_door **lst, t_door *new)
// {
// 	t_door	*temp;

// 	if (!new)
// 		return ;
// 	temp = *lst;
// 	*lst = new;
// 	new->next = temp;
// 	new->prev = NULL;
// }

void	ft_lstadd_back1(t_door **lst, t_door *new)
{
	t_door	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast1(*lst);
	last->next = new;
	new->prev = last;
}