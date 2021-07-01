#include "mshell.h"

char	*rl_gets_without_hist(char *promt, int *error)
{
	char	*line;

	line = term_readline(promt, error);
	if (line == NULL && *error == 0)
		*error = 130;
	else
		write(1, "\n", 1);
	return (line);
}
