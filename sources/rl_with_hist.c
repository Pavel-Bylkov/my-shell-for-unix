#include "my_shell.h"

void		int_handler(int status)
{
	if (status == SIGINT)
	{
		write(1, "\e[2D  \e[2D", 10);
		write(1, "\n", 1);
		// rl_on_new_line(); // Regenerate the prompt on a newline
		// rl_replace_line("", 0); // Clear the previous text
		// rl_redisplay();
		open_close_fd(NULL);
		exit(20);
	}
	if (status == SIGQUIT)
	{
		write(1, "\e[2D  \e[2D", 10);
	}
}

void		child_readline2(int *fd, char *promt)
{
	char	*line;

	rl_catch_signals = 0;
	signal(SIGINT, int_handler);
	signal(SIGQUIT, int_handler);
	write(1, "child start\n", 12);
	line = readline(promt);
	if (line != NULL)
	{
		write(fd[1], line, ft_strlen(line));
		open_close_fd(NULL);
	}
	else
	{
		open_close_fd(NULL);
		exit(130);
	}
	exit(0);
}

char 		*rl_gets_with_add_hist(char *promt, int *error)
{
	char	*line;
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	line = NULL;
	if (pid == 0)
	{
		open_close_fd(fd);
		child_readline2(fd, promt);
	}	
	// waitpid(0, error, 0);
	wait(error);
	*error = WEXITSTATUS(*error);
	ft_putnbr_fd(*error, 2);
	write(1, "child end\n", 10);
	if (*error == 130)
	{
		write(1, "child 130\n", 10);
		line = NULL;
	}
	else if (*error == 1)
	{
		write(1, "child 1\n", 8);
		line = ft_strdup("");
	}
	else
		line = read_line_from_fd(fd);
	if (line && *line)
		add_history(line);
	close(fd[1]);
	close(fd[0]);
	write(1, "dddd\n", 5);
	return (line);
}