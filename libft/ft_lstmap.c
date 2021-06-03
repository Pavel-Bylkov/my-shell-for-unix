/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:49:54 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 18:22:27 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;
	t_list	*start;

	new = NULL;
	if (lst != NULL)
	{
		start = new;
		while (lst != NULL)
		{
			elem = ft_lstnew((*f)(lst->content));
			if (elem == NULL)
			{
				ft_lstclear(&start, del);
				return (NULL);
			}
			ft_lstadd_back(&new, elem);
			if (start == NULL)
				start = new;
			lst = lst->next;
		}
	}
	return (new);
}
