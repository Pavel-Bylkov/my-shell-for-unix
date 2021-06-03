/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:59:57 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 16:22:31 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*rez;

	rez = *lst;
	if (*lst != NULL)
	{
		while (rez->next != NULL)
			rez = rez->next;
		rez->next = new;
	}
	else
		*lst = new;
}
