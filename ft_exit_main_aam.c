#include "my_shell.h"

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
	write(1, "exit\n", 5);
	if (ft_isnum_aam(par.argv[1]) == 1)
		ft_exit_output_err(NULL, ": too many arguments");
	else
	{
		ft_exit_output_err(par.argv[1], ": numeric argument required");
		exit(-1);
	}
	return (code);
}

void	ft_exit_two(t_pars par)
{
	int	num;

	num = 0;
	if (ft_isnum_aam(par.argv[1]) == 1)
	{
		write(1, "exit\n", 5);
		num = ft_atoi(par.argv[1]);
		exit(num);
	}
	else
	{
		write(1, "exit\n", 5);
		ft_exit_output_err(par.argv[1], ": numeric argument required");
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
	else if (par.argv[1] != NULL && par.argv[2] != NULL)
		code = ft_exit_one(1, par);
	else if (par.argv[1] == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else
		ft_exit_two(par);
	return (code);
}
