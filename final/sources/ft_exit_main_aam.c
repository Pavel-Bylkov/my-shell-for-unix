/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_main_aam.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 08:33:39 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/30 14:25:08 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum_aam(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '-' || str[i] == '+'))
		{
			if (i > 0)
				return (0);
			else
				i++;
		}
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit_one(int code, t_pars par)
{
	if (ft_isnum_aam(par.argv[1]) == 1)
		ft_output_err_aam(code, "exit: ", ": too many arguments\n", NULL);
	else
	{
		ft_output_err_aam(code, "exit: ", par.argv[1],
			": numeric argument required\n");
		exit(-1);
	}
	return (code);
}

void	ft_exit_two(t_pars par)
{
	int	num;

	num = check_number(par.argv[1]);
	if (num != -1)
		exit(num);
	else
	{
		ft_output_err_aam(-1, "exit: ", par.argv[1],
			": numeric argument required\n");
		exit(-1);
	}
}

int	ft_exit_token(int code, t_pars par)
{
	int		pos;

	pos = ft_char_in_str(par.argv[1], ')');
	if (pos == 1)
		return (ft_output_err_aam(code, "syntax error near unexpected token `",
				"newline'\n", NULL));
	par.argv[1][pos] = '\0';
	return (ft_output_err_aam(code, "syntax error near unexpected token `",
			&par.argv[1][1], "'\n"));
	return (code);
}

int	ft_exit(t_pars par)
{
	int		code;

	code = 0;
	if (par.argv[1] != NULL && (par.argv[1][0] == '(' || par.argv[1][0] == ')'))
		code = ft_exit_token(258, par);
	else
	{
		if (par.counter <= 1)
			write(1, "exit\n", 5);
		if (par.argv[1] != NULL && par.argv[2] != NULL)
			code = ft_exit_one(1, par);
		else if (par.argv[1] == NULL)
			exit(0);
		else
			ft_exit_two(par);
	}
	return (code);
}
