/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_err_aam.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:56:25 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/29 11:05:44 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_output_err(int code, char *str)
{
	write(2, "env: ", 5);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	return (code);
}

int	ft_export_output_err(int code, char *str)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	write(2, "export: ", 8);
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (code);
}

int	ft_output_err_aam(int code, char *str1, char *str2, char *str3)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	if (str1 != NULL)
		write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	if (str3 != NULL)
		write(2, str3, ft_strlen(str3));
	return (code);
}

int	ft_command_err_slesh(char *name_f)
{
	struct stat	buff;

	if (opendir(name_f) != NULL)
		return (ft_output_err_aam(126, name_f, ": is a directory\n", NULL));
	else
	{
		if (stat(name_f, &buff) >= 0)
			return (ft_output_err_aam(126, name_f,
					": Permission denied\n", NULL));
		if (stat(name_f, &buff) >= 0)
			return (ft_output_err_aam(127, name_f,
					": Not a directory\n", NULL));
		return (ft_output_err_aam(127, name_f,
				": No such file or directory\n", NULL));
	}
}

int	ft_command_err_aam(char *name_f)
{
	struct stat	buff;

	if (name_f[0] == '.' && name_f[1] == '\0')
		return (ft_output_err_aam(1, name_f,
				": filename argument required\n",
				".: usage: . filename [arguments]\n"));
	if (name_f[0] == '.' && name_f[1] == '.' && name_f[2] == '\0')
		return (ft_output_err_aam(127, name_f, ": command not found\n", NULL));
	if (ft_char_in_str(name_f, '/') < (int)ft_strlen(name_f))
		return (ft_command_err_slesh(name_f));
	if (stat(name_f, &buff) < 0)
		return (ft_output_err_aam(127, name_f,
				": No such file or directory\n", NULL));
	return (ft_output_err_aam(127, name_f, ": command not found\n", NULL));
}
