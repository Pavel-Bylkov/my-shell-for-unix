/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  check_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			how_is_how(char *str, int i)
{
	if (ft_isalpha(str[i]) || ft_isdigit(str[i]) ||
				ft_strnchr(".*_@#$~!%%^[]{}:?-=+`/,", str[i]) != -1)
		return (5); 
	if (quaote_is_open(str, i) == 0 
			&& backslash_is_active(str, i) == 0)
	{
		if (str[i] == ' ')
			return (6);
		if (str[i] == ')' && brackets_is_open(str, i) < 0)
			return (7);
		if (str[i] == '(')
			return (8);
		if (str[i] == '>')
			return (9);
		if (str[i] == '<')
			return (10);
		return (ft_strnchr("|;&", str[i]));
	}
	return (3);
}

int			count_chr(char *str, char c, int n)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] && i <= n)
	{
		if (str[i] == c)
			count++;
		else
			count = 0;
	}
	return (count);
}

int			check_spec_redir(char *str, int i, int flag)
{
	int	j;
	int	f;

	j = i;
	f = 0;
	if (flag >= 0 && flag <= 2)
	{
		while (--j > -1 && how_is_how(str, j) > 2 && f == 0)
			f = (how_is_how(str, j) == 5 || how_is_how(str, j) == 3);
		if (f == 0 && count_chr(str, str[i], i) != 2)
			return (unexpected_token(ft_strdupn(&str[i], 
					1 + (ft_strnchr("|&", str[i + 1]) > -1)), 1));
	}
	if (flag > 8)
	{
		while (--j > -1 && how_is_how(str, j) > 8)
			f++;
		if (f > 1)
			return (unexpected_token(ft_strdupn(&str[i], 1), 1));
	}
	return (0);
}

int			check_brakets(char *str, int i, int flag)
{
	int	j;
	int	f[2];

	if (flag == 8 && i - 1 > -1 && str[i - 1] != '<')
	{
		j = i;
		f[0] = 0;
		f[1] = 0;
		while (--j > -1 && how_is_how(str, j) > 2 && how_is_how(str, j) < 9)
		{
			if (how_is_how(str, j) == 5)
				f[0] = 1;
			else if (f[0] == 1 && how_is_how(str, j) == 6)
				f[1] = f[0]++;
		}
		if (f[0] == 1 && f[1] == 1)
			return (unexpected_token("(", 0));
		if ((f[0] == 1 && f[1] == 0) || (f[0] == 2 && f[1] == 1))
			return (unexpected_token(ft_g_strdupanychr(&str[i + 1], ") "), 1));
	}
	return (0);
}

int			check_unexpected_token(char *str)
{
	int		flag;
	int		i;
	int		error;

	i = -1;
	flag = -1;
	error = 0;
	while (str[++i] && error == 0)
	{
		flag = how_is_how(str, i);
		if (flag == 7)
			return (unexpected_token(")", 0));
		if (flag == 1 && str[i + 1] == ';' && str[i + 2] == '&')
			return (unexpected_token(";;&", 0));
		if (flag == 1 && str[i + 1] == ';')
			return (unexpected_token(";;", 0));
		if (flag > 7 && str[i + 1] == '\0')
			return (unexpected_token("newline", 0));
		error += check_spec_redir(str, i, flag);
		error += check_brakets(str, i, flag);
	}
	return (error);
}
