#include "my_shell.h"

int	ft_echo(t_pars pars)
{
	int	i;

	i = 0;
	while (pars.argv[++i])
	{
		if (ft_strcmp(pars.argv[i], "-n"))
		{
			write(1, pars.argv[i], ft_strlen(pars.argv[i]));
			if (pars.argv[i + 1])
				write(1, " ", 1);
		}
	}
	if (ft_strcmp(pars.argv[1], "-n"))
		write(1, "\n", 1);
	return (0);
}
