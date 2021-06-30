/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/06/30 10:13:13 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirects(char *str, int *i, char *s)
{
	return (ft_strncmp(&str[i[0]], s, 2) == 0
		&& backslash_is_active(str, i[0]) == 0
		&& quaote_is_open(str, i[0]) == 0);
}

void	ft_redir_add(t_redir **lst, t_redir *new)
{
	t_redir	*last;

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

void	create_redir_stdin(t_redir	*rez, t_data *data)
{
	rez->f_spec[0] = '<';
	rez->f_spec[1] = '\0';
	rez->out = ft_strdup(get_filename_by_index(data->tmp_files,
				data->count_files));
	data->count_files -= 1;
}

t_redir	*ft_redirnew(t_data *data, int l1, int l2)
{
	t_redir	*rez;
	int		j;

	rez = (t_redir *)malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	if (ft_strncmp(data->tmp_fcpec, "<<", 2) != 0)
	{
		j = -1;
		while (++j != l1)
			rez->f_spec[j] = data->tmp_fcpec[j];
		rez->f_spec[j] = '\0';
		rez->out = ft_strdupn(data->tmp_out, l2);
	}
	else
		create_redir_stdin(rez, data);
	rez->next = NULL;
	data->tmp_fcpec = NULL;
	data->tmp_out = NULL;
	return (rez);
}

void	ft_redirclear(t_redir **redir)
{
	t_redir	*tmp;

	while (*redir)
	{
		tmp = (*redir)->next;
		if ((*redir)->out)
			ft_free((void **)&((*redir)->out));
		ft_free((void **)redir);
		*redir = tmp;
	}
}
