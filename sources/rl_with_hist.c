#include "mshell.h"

void	int_handler(int status)
{
	if (status == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data->code_exit = 1;
	}
	return ;
}

void	int_handler2(int status)
{
	if (status == SIGINT)
		write(1, "\n", 1);
	if (status == SIGQUIT)
		write(1, "\e[2D", 4);
	return ;
}

char 	*rl_gets_with_add_hist(char *promt)
{
	char	*line;

	rl_catch_signals = 0;
	signal(SIGINT, int_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline(promt);
	if (line == NULL)
	{
		write(1, "\e[A\e[D", 6);
		ft_putstr_fd(promt, 1);
	}
	if (line && *line)
		ft_add_history(line);
	signal(SIGINT, int_handler2);
	signal(SIGQUIT, int_handler2);
	return (line);
}
