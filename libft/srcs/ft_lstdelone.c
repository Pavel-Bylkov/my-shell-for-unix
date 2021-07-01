#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*head;

	if (lst != NULL && del != NULL)
	{
		head = lst->next;
		(*del)(lst->content);
		free(lst);
		lst = head;
	}
}
