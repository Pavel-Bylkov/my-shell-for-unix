/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fspec_commands(char **str, char *f_spec)
{
	int	len;
	int	i;

	len = ft_strlen(*str);
	i = 0;
	if (len > 0 && chr_in_str((*str)[len - 1], "|;&") > -1)
	{
		f_spec[i++] = (*str)[len - 1];
		(*str)[len - 1] = '\0';
		if (len > 1 && chr_in_str((*str)[len - 2], "|&") > -1)
		{
			f_spec[i++] = (*str)[len - 2];
			(*str)[len - 2] = '\0';
		}
	}
	f_spec[i] = '\0';
}

int		str_is_fd(char *str, int n)
{
	int		i;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] == ' ')
			i++;
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	save_argv(char *str, char **argv, int *i)
{
	i[1] = i[0];
	while (str[i[1]] && ((!is_redir(str[i[1]]) && str[i[1]] != ' ')
			|| (quaote_is_open(str, i[1]) != 0
			|| backslash_is_active(str, i[1]) != 0)))
		i[1]++;
	if (!is_redir(str[i[1]]) || !str_is_fd(&str[i[0]], i[1] - i[0]))
	{
		while (str[i[0]] && i[0] < i[1])
			(*argv)[++i[2]] = str[i[0]++];
		(*argv)[++i[2]] = ' ';
	}
	i[0] = i[1];
}

void	get_argv(char *str, char **argv)
{
	int		i[4];

	i[0] = -1;
	i[2] = -1;
	while (str[++i[0]])
	{
		save_argv(str, argv, i);
		if (is_redir(str[i[0]]))
		{
			while (is_redir(str[i[0]]))
				i[0]++;
			while (str[i[0]] == ' ')
				i[0]++;
			while (str[i[0]] && (str[i[0]] != ' '
					|| (quaote_is_open(str, i[0]) != 0
					|| backslash_is_active(str, i[0]) != 0)))
				i[0]++;
		}
		i[0] -= (str[i[0]] == '\0');
	}
	(*argv)[++i[2]] = '\0';
}

t_pars	*pars_command(char *str, t_data *data)
{
	t_pars		*new;
	char 		f_spec[10];
	char		*argv;

	argv = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_memset(argv, 0, sizeof(argv));
	get_fspec_commands(&str, f_spec);
	get_argv(str, &argv);
	new = ft_parsnew(0, NULL, argv_split(argv), f_spec);
	ft_free(&argv);
	new->redirect = get_redirects(str, data);
	return (new);
}
