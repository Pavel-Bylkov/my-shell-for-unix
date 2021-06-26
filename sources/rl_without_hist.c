#include "my_shell.h"

void		int_handler2(int status)
{
	if (status == SIGINT)
	{
		// write(1, "\e[2D  \e[2D", 10);
		exit(1);
	}
}

void		child_readline(int *fd, char *promt)
{
	char	*line;

	signal(SIGINT, int_handler2);
	line = readline(promt);
	if (line != NULL)
	{
		write(fd[1], line, ft_strlen(line));
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
		exit(130);
	}
	exit(0);
	signal(SIGINT, SIG_DFL);
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
		child_readline(fd, promt);
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
	return (line);
}