#include "my_shell.h"

void		int_handler2(int status)
{
	if (status == SIGINT)
	{
		// signal(SIGQUIT, SIG_DFL);
		// rl_on_new_line(); // Regenerate the prompt on a newline
    	// rl_replace_ine("", 0); // Clear the previous text
		// rl_cleanup_after_signal();
		open_close_fd(NULL, 1);
		// _exit(1);
	}
	return ;
}

void		child_readline(int *fd, char *promt)
{
	char	*line;

	rl_catch_signals = 0;
	signal(SIGINT, int_handler2);
	// signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	line = readline(promt);
	if (line != NULL)
	{
		write(fd[1], line, ft_strlen(line));
		open_close_fd(NULL, 0);
	}
	else
	{
		write(1, "\e[A\e[D", 6);
		ft_putstr_fd(promt, 1);
		open_close_fd(NULL, 0);
		exit(130);
	}
	exit(0);
}

void	kill_child(pid_t pid)
{
	static pid_t	savepid;

	if (pid != 0)
		savepid = pid;
	else
		kill(savepid, SIGTERM);
}

void	sighandler3(int status)
{
	if (status == SIGINT)
	{
		kill_child(0);
	}
	return ;
}

char	*read_line_from_fd(int *fd)
{
	char	*line;
	char    buf[1024];
	int		r;
	char	*tmp;
	
	r = 1;
	line = ft_strdup("");
	r = read(fd[0], buf, 1022);
	while (r > 0)
	{
		buf[r] = '\0';
		tmp = line;
		line = ft_strjoin(tmp, buf);
		free(tmp);
		if (r == 1022)
			r = read(fd[0], buf, 1022);
		else
			r = 0;
	}
	return (line);
}

char 		*rl_gets_without_hist(char *promt, int *error)
{
	char	*line;
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	line = NULL;
	if (pid == 0)
	{
		open_close_fd(fd, 0);
		child_readline(fd, promt);
	}
	else
	{
		signal(SIGINT, sighandler3);
		// signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		kill_child(pid);
		waitpid(0, error, 0);
		*error = WEXITSTATUS(*error);
		if (*error == 130)
			line = NULL;
		else if (*error == 1)
		{
			if (errno == EINTR) // не помогает
				errno = 0;
			write(1, "\n", 1);
			line = ft_strdup("");
		}
		else
			line = read_line_from_fd(fd);
		close(fd[1]);
		close(fd[0]);
	}
	return (line);
}