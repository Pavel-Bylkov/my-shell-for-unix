/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_perr(char *com, int code, char *str1, char *str2)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	if (com)
	{
		ft_putstr_fd(com, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str1)
		ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (code);
}

int		unexpected_eof(char *str)
{
	char 	*str_err;
	int		len;

	str_err = ft_strdup("unexpected EOF while looking for matching `");
	len = ft_strlen(str);
	if (quaote_is_open(str, len) == 1)
		str_err = ft_g_strjoin(str_err, 0, 0, ft_strdup("''"));
	else if (quaote_is_open(str, len) == 2)
		str_err = ft_g_strjoin(str_err, 0, 0, ft_strdup("\"'"));
	else if (brackets_is_open(str, len) > 0)
		str_err = ft_g_strjoin(str_err, 0, 0, ft_strdup(")'"));
	ft_perr(NULL, 258, NULL, str_err);
	ft_free((void **)&str_err);
	ft_free((void **)&str);
	return (258);
}

int		unexpected_eof_infile(char *str)
{
	char	*strerr;

	strerr = ft_strjoin(
			"here-document at line 1 delimited by end-of-file (wanted `",
			str);
	strerr = ft_g_strjoin(strerr, 0, 0, ft_strdup("')"));
	ft_perr("warning", 0, NULL, strerr);
	free(strerr);
	return (0);
}

int		unexpected_token(char *str, int flag)
{
	char	*strerr;

	strerr = ft_strjoin(
			"syntax error near unexpected token `", str);
	strerr = ft_g_strjoin(strerr, 0, 0, ft_strdup("'"));
	ft_perr(NULL, 258, NULL, strerr);
	free(strerr);
	if (flag)
		ft_free((void **)&str);
	return (258);
}
