#include "my_shell.h"

char 		*rl_gets_without_hist(char *promt, int *error)
{
	char	*line;

	line = term_readline(promt, error);
	if (line == NULL && *error == 0)
	{
		//write(1, "\e[A\e[D", 6);
		//ft_putstr_fd(promt, 1);
		*error = 130;
	}
	else
		write(1, "\n", 1);
	return (line);
}