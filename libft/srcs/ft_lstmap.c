/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:20:34 by whector           #+#    #+#             */
/*   Updated: 2021/03/24 15:20:40 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_clean(t_list *start, void (*del)(void *))
{
	t_list	*next;

	while (start)
	{
		next = start->next;
		(*del)(start->content);
		free(start);
		start = next;
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
								void (*del)(void *))
{
	t_list	*elem;
	t_list	*result;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	result = NULL;
	tmp = lst;
	while (tmp != NULL)
	{
		elem = ft_lstnew((*f)(tmp->content));
		if (elem == NULL)
			return (ft_clean(result, (*del)));
		ft_lstadd_back(&result, elem);
		tmp = tmp->next;
	}
	return (result);
}
