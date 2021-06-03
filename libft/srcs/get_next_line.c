
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
	if (*cur && (p_n = gnl_str_endl(*cur)))
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

int				get_next_line(int fd, char **line)
{
	static char	*arr[1025];
	char		*buf;
	ssize_t		i;
	char		*p_n;
	char		*tmp;

	if (fd < 0 || fd > 1024 || !line || BUFFER_SIZE < 1
			|| !(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	*line = NULL;
	if (read(fd, buf, 0) < 0)
		return (free_str(&arr[fd], &buf));
	while ((i = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[i] = '\0';
		tmp = arr[fd];
		if (!(arr[fd] = gnl_strjoin(tmp, buf)))
			return (free_str(&tmp, &buf));
		if (tmp != NULL)
			free(tmp);
		if ((p_n = gnl_str_endl(arr[fd])))
			return (get_cur_line(&arr[fd], line, p_n, &buf));
	}
	return (eof_checker(&arr[fd], line, i, &buf));
}
