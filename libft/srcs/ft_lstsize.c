#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*cur;
	int		n;

	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (1);
	n = 1;
	cur = lst;
	while (cur->next != NULL)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}
