/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:06:23 by aamarei           #+#    #+#             */
/*   Updated: 2020/12/19 21:12:41 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_gnl_work(int fd, char **str, char **remainder)
{
	char		*buf;
	int			n;

	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((n = read(fd, buf, BUFFER_SIZE)))
	{
		buf[n] = '\0';
		if ((n = ft_in_set(buf, '\n')) == 0)
			*str = ft_strjoin(*str, buf);
		else
		{
			buf[n - 1] = '\0';
			*str = ft_strjoin(*str, buf);
			*remainder = ft_strjoin(*remainder, &buf[n]);
			free(buf);
			if (!(*str) || !(*remainder))
				return (-1);
			return (1);
		}
		if (!(*str))
			return (-1);
	}
	free(buf);
	return (0);
}

int			next_line(int fd, int n, char **remainder, char **line)
{
	*line = ft_strjoin(*line, *remainder);
	if (!*remainder)
		if (!(*remainder = (char*)malloc(1)))
			return (-1);
	**remainder = '\0';
	n = ft_gnl_work(fd, line, remainder);
	if (!*line || n == -1)
		free(*line);
	return (n);
}

int			get_next_line(int fd, char **line)
{
	static char	*remainder;
	int			n;
	char		buf[1];

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = (char *)malloc(1);
	*line[0] = '\0';
	if (!(n = ft_in_set(remainder, '\n')))
		return (next_line(fd, n, &remainder, line));
	else
	{
		remainder[n - 1] = '\0';
		*line = ft_strjoin(*line, remainder);
		remainder = ft_trim(remainder, n);
		if (!(*line) || !remainder)
		{
			free(*line);
			free(remainder);
			return (-1);
		}
	}
	return (1);
}
