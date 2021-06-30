/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pars(t_data *data)
{
	t_pars *tmp;
	t_redir *last;
	int		i;

	tmp = data->curr_pars;
	while (tmp != NULL)
	{
		printf("------------------------------------\n");
		printf("count : %d\ncounter : %d\n", tmp->count, tmp->counter);
		printf("error : %d\npath : %s\nargv :\n", tmp->error, tmp->path);
		i = -1;
		while (tmp->argv[++i] != NULL)
			printf("   %d : |%s|\n", i, tmp->argv[i]);
		printf("f_spec : %s\nredirects :\n", tmp->f_spec);
		last = tmp->redirect;
		while (last != NULL)
		{
			printf("  -f_spec : %s\n  -out : |%s|\n", last->f_spec, last->out);
			last = last->next;
		}
		tmp = tmp->next;
	}
}

int run_comands(t_data *data, int error)
{
	if (error != 0)
		return (error);
    return (aam_main(data));
}

char	*ft_newpath(char *dir, int n, char *name)
{
	char	*res;
	char	*tmp;
	char	*dir_tmp;

	dir_tmp = ft_strdupn(dir, n);
	tmp = ft_strjoin(dir_tmp, "/");
	res = ft_strjoin(tmp, name);
	ft_free((void **)&dir_tmp);
	ft_free((void **)&tmp);
	return (res);
}

int		is_spec_chr(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}
