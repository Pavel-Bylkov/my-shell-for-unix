#include "my_shell.h"

void		int_handler2(int status)
{
	if (status == SIGINT)
	{
		open_close_fd(NULL, 1);
		// _exit(1);
	}
	return ;
}

void		child_readline(int *fd, char *promt)
{
	char	*line;

	
	if (line != NULL)
	{
		write(fd[1], line, ft_strlen(line));
		open_close_fd(NULL, 0);
	}


char 		*rl_gets_without_hist(char *promt, int *error)
{
	char	*line;

	signal(SIGINT, int_handler2);
	signal(SIGQUIT, SIG_IGN);
	line = term_readline(promt);
	if (line == NULL)
	{
		//write(1, "\e[A\e[D", 6);
		//ft_putstr_fd(promt, 1);
		*error == 130;
	}
	else if (*line = '\0')
	{
		write(1, "\n", 1);
		*error == 1
	}
	return (line);
}