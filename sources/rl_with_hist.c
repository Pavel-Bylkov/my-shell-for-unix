#include "my_shell.h"

void		int_handler(int status)
{
	if (status == SIGINT)
	{
		// write(1, "  \e[2D", 6);
		write(1, "\n", 1);
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
		g_data->code_exit = 1;
	}
	return ;
}

char 		*rl_gets_with_add_hist(char *promt)
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
		add_history(line);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (line);
}

void		open_close_fd(int *fd, int k)
{
	static int	*fd_static;

	if (fd != NULL)
	{
		fd_static = (int *)malloc(sizeof(int) * 2);
		fd_static[0] = fd[0];
		fd_static[1] = fd[1];
	}
	else
	{
		close(fd_static[0]);
		close(fd_static[1]);
		if (fd_static != NULL)
		{
			free(fd_static);
			fd_static = NULL;
		}
		
		if (k == 1)
		{
			rl_catch_signals = 1;
			// signal(SIGINT, SIG_DFL);
			// signal(SIGQUIT, SIG_DFL);
		}
	}
}
