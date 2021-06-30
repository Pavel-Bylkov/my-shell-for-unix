/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:06:23 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/30 18:16:04 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_exit_free(char **line, char *remainder)
{
	if (*line)
		free(*line);
	if (remainder)
		free(remainder);
	return (-1);
}

int	add_str_in_line(char **str, char *buf, char **remainder, int n)
{
	if (n == 0)
		*str = ft_strjoin_gnl(*str, buf);
	else
	{
		buf[n - 1] = '\0';
		*str = ft_strjoin_gnl(*str, buf);
		*remainder = ft_strjoin_gnl(*remainder, &buf[n]);
		free(buf);
		if (!(*str) || !(*remainder))
			return (-1);
		return (1);
	}
	return (0);
}

int	ft_gnl_work(int fd, char **str, char **remainder)
{
	char		*buf;
	int			n;
	int			k;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		buf[n] = '\0';
		n = ft_in_set(buf, '\n');
		k = add_str_in_line(str, buf, remainder, n);
		if (k != 0)
			return (k);
		if (!(*str))
			return (-1);
		n = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (0);
}

int	next_line(int fd, int n, char **remainder, char **line)
{
	*line = ft_strjoin_gnl(*line, *remainder);
	if (!*remainder)
	{
		*remainder = (char *)malloc(1);
		if (!(*remainder))
			return (-1);
	}
	**remainder = '\0';
	n = ft_gnl_work(fd, line, remainder);
	if (!*line || n == -1)
		free(*line);
	return (n);
}

int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	int			n;
	char		buf[1];

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = (char *)malloc(1);
	*line[0] = '\0';
	n = ft_in_set(remainder, '\n');
	if (!n)
		return (next_line(fd, n, &remainder, line));
	else
	{
		remainder[n - 1] = '\0';
		*line = ft_strjoin_gnl(*line, remainder);
		remainder = ft_trim(remainder, n);
		if (!(*line) || !remainder)
			return (ft_exit_free(line, remainder));
	}
	return (1);
}
