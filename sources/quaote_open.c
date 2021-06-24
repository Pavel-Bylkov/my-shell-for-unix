#include "my_shell.h"

void		int_handler2(int status)
{
	if (status == SIGINT)
	{
		write(1, "\b\b  ", 4);
		write(1, "\n", 1);
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

int			is_endl_ignor(char *str, t_data *data)
{
	int		len;

	len = ft_strlen(str);
	return (backslash_is_active(str, len) ||
			quaote_is_open(str, len) != 0 || str[len - 1] == '|'
				|| ft_strncmp(&str[len - 2], "&&", 2) == 0 ||
				brackets_is_open(str, len) > 0 || ft_stdin_active(str, data));
}

char	*get_line_slash(char *line, char *tmp, int *error)
{
	line = rl_gets_without_hist(QUAOTE_PROMT, error);
	if (NULL == line)
		exit(0);
	line = g_strjoin(tmp, -1, 0, line);
	add_history(line);
	return (line);
}

char	*get_line_quaote(char *line, char *tmp, int *error, int len)
{
	line = rl_gets_without_hist(QUAOTE_PROMT, error);
	if (NULL == line)
		return (NULL);
	else if (quaote_is_open(tmp, len) != 0)
		line = g_strjoin(tmp, 0, 1, line);
	else
		line = g_strjoin(tmp, 0, 0, line);
	add_history(line);
	return (line);
}



int		quaote_open_mode(t_data *data)
{
	int		len;
	char	*tmp;
	int		error;

	len = ft_strlen(data->line);
	error = 0;
	if (check_unexpected_token(data->line) != 0)
		return (258);
	while (is_endl_ignor(data->line, data) && error == 0)
	{
		tmp = data->line;
		if (backslash_is_active(tmp, len))
			data->line = get_line_slash(data->line, tmp, &error);
		else if (ft_stdin_active(tmp, data))
			error = read_tmp_stdin(data, tmp);
		// если скобка - подставить ; и убрать \n
		else
		{
			data->line = get_line_quaote(data->line, tmp, &error, len);
			if (NULL == data->line)
				return (unexpected_eof(tmp));
		}
		len = ft_strlen(data->line);
	}
	if (error == 258)
		ft_perr("syntax error", 258, NULL, "unexpected end of file");
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	return (error);
}