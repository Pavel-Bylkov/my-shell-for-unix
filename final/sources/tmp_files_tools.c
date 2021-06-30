/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_files_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_tmp_files_clear(t_tmp_files **lst)
{
	t_tmp_files	*head;
	t_tmp_files	*tmp;

	if (*lst != NULL)
	{
		head = *lst;
		unlink(head->fname);
		ft_free((void **)&(head->fname));
		head = head->next;
		ft_free((void **)lst);
		while (head != NULL)
		{
			tmp = head->next;
			unlink(head->fname);
			ft_free((void **)&(head->fname));
			ft_free((void **)&head);
			head = tmp;
		}
		*lst = NULL;
	}
}

t_tmp_files		*tmp_files_new(int index, char *fname)
{
	t_tmp_files	*new;

	new = (t_tmp_files *)malloc(sizeof(t_tmp_files));
	if (new == NULL)
		return (NULL);
	new->index = index;
	new->fname = fname;
	new->next = NULL;
	return (new);
}

int				tmp_files_size(t_tmp_files *lst)
{
	t_tmp_files	*cur;
	int			n;

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

void			tmp_files_add_back(t_tmp_files **lst, t_tmp_files *new)
{
	t_tmp_files	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

char			*get_filename_by_index(t_tmp_files *head, int index)
{
	t_tmp_files *tmp;

	if (head == NULL)
		return (NULL);
	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->index == index)
			return (tmp->fname);
		tmp = tmp->next;
	}
	return (NULL);
}
