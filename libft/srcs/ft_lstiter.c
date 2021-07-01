#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*elem;

	if (lst != NULL && f != NULL)
	{
		elem = lst;
		while (elem != NULL)
		{
			(*f)(elem->content);
			elem = elem->next;
		}
	}
}
