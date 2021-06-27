#include "my_shell.h"

void		open_close_fd(int *fd)
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
		free(fd_static);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
		
}

void		int_handler2(int status)
{
	if (status == SIGINT)
	{
		// write(1, "\e[2D  \e[2D", 10);
		open_close_fd(NULL);
		exit(1);
	}
	if (status == SIGQUIT)
	{
		write(1, "", 0);
	}
}
void		int_handler3(int status)
{
	if (status == SIGINT)
	{
		write(1, "", 0);
	}
	if (status == SIGQUIT)
	{
		write(1, "", 0);
	}
}

void		child_readline(int *fd, char *promt)
{
	char	*line;

	rl_catch_signals = 0;
	signal(SIGINT, int_handler2);
	signal(SIGQUIT, int_handler2);
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

	signal(SIGINT, int_handler3);
	signal(SIGQUIT, int_handler3);
	pipe(fd);
	pid = fork();
	line = NULL;
	if (pid == 0)
	{
		open_close_fd(fd);
		child_readline(fd, promt);
	}
	waitpid(0, error, 0);
	*error = WEXITSTATUS(*error);
	if (*error == 130)
		line = NULL;
	else if (*error == 1)
		line = ft_strdup("");
	else
		line = read_line_from_fd(fd);
	close(fd[1]);
	close(fd[0]);
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	return (line);
}