/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:18:56 by whector           #+#    #+#             */
/*   Updated: 2021/03/24 15:18:58 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;
	t_list	*tmp;

	if (*lst != NULL && del != NULL)
	{
		head = *lst;
		(*del)(head->content);
		head = head->next;
		free(*lst);
		while (head != NULL)
		{
			tmp = head->next;
			(*del)(head->content);
			free(head);
			head = tmp;
		}
		*lst = NULL;
	}
}
