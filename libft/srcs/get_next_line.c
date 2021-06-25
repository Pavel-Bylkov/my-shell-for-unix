
#include "get_next_line.h"

static int		free_str(char **cur, char **buf)
{
	if (*cur != NULL)
		free(*cur);
	*cur = NULL;
	if (*buf != NULL)
		free(*buf);
	*buf = NULL;
	return (-1);
}

static int		get_cur_line(char **cur, char **line, char *p_n, char **buf)
{
	char	*new;

	*p_n = '\0';
	if (!(*line = gnl_strdup(*cur)))
		return (free_str(cur, buf));
	if (!(new = gnl_strdup(++p_n)))
	{
		free(*line);
		*line = NULL;
		return (free_str(cur, buf));
	}
	free_str(cur, buf);
	*cur = new;
	return (1);
}

static int		eof_checker(char **cur, char **line, ssize_t i, char **buf)
{
	char	*p_n;
	char	empty[1];

	if (i < 0)
		return (free_str(cur, buf));
	p_n = gnl_str_endl(*cur);
	if (*cur && p_n)
		return (get_cur_line(cur, line, p_n, buf));
	if (*cur != NULL)
	{
		*line = *cur;
		*cur = NULL;
		free_str(cur, buf);
		return (0);
	}
	empty[0] = '\0';
	*line = gnl_strdup(empty);
	if (*line == NULL)
		return (free_str(cur, buf));
	free_str(cur, buf);
	return (0);
}

int				read_lines(t_rl_my	*tmp, int fd, char **line)
{
	ssize_t		i;

	i = read(fd, tmp->buf, BUFFER_SIZE);
	while (i > 0)
	{
		tmp->buf[i] = '\0';
		tmp->tmp = tmp->arr;
		tmp->arr = gnl_strjoin(tmp, tmp->buf);
		if (!tmp->arr)
			return (free_str(&tmp, &(tmp->buf)));
		if (tmp != NULL)
			free(tmp);
		tmp->p_n = gnl_str_endl(tmp->arr);
		if (tmp->p_n)
			return (get_cur_line(&(tmp->arr), line, tmp->p_n, &(tmp->buf)));
		i = read(fd, tmp->buf, BUFFER_SIZE);
	}
	return (eof_checker(&(tmp->arr), line, i, &(tmp->buf)));
}

int				get_next_line(int fd, char **line)
{
	static char	*arr[1025];
	t_rl_my		tmp;

	if (BUFFER_SIZE > 0)
		tmp.buf = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || fd > 1024 || !line || BUFFER_SIZE < 1 || !tmp.buf)
		return (-1);
	*line = NULL;
	tmp.arr = arr[fd];
	if (read(fd, tmp.buf, 0) < 0)
		return (free_str(&(tmp.arr), &(tmp.buf)));
	return (read_lines(&tmp, fd, line));
}
