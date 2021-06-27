#include "my_shell.h"

int	ft_echo_option_n(char *str)
{
	int		i;

	if (ft_strncmp(str, "-n", 2) == 0)
	{
		i = 1;
		while (str[++i] != '\0')
			if (str[i] != 'n')
				return (0);
	}
	else
		return (0);
	return (1);
}

int	ft_echo(t_pars pars)
{
	int	i;
	int	fl;

	fl = 0;
	i = 0;
	while (pars.argv[++i])
	{
		if (!(pars.argv[i] && fl == 0 && ft_echo_option_n(pars.argv[i])))
		{
			fl = 1;
			write(1, pars.argv[i], ft_strlen(pars.argv[i]));
			if (pars.argv[i + 1])
				write(1, " ", 1);
		}
	}
	if (pars.argv[1] && ft_echo_option_n(pars.argv[1]) == 0)
		write(1, "\n", 1);
	else if (!pars.argv[1])
		write(1, "\n", 1);
	return (0);
}
