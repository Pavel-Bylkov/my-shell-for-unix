/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:04:49 by aamarei           #+#    #+#             */
/*   Updated: 2020/11/07 17:33:02 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*rez;

	rez = (t_list *)malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	rez->content = content;
	rez->next = NULL;
	return (rez);
}
