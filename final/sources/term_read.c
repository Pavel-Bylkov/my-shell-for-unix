/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_close_fd(int k, int fd)
{
	static int	savefd;

	if (k == 0)
	{
		savefd = fd;
		signal(SIGINT, handler_close);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		if (savefd > 0)
		{
			close(savefd);
			savefd = 0;
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
		}
	}	
}

void	handler_close(int sig)
{
	if (sig == SIGINT)
		open_close_fd(1, 0);
	return ;
}

int		read_next_chr(int fd, char *str, int *error)
{
	int		l;

	ft_memset(str, 0, 5);
	l = read(fd, str, 5);
	if (l < 0)
		*error = 1;
	return (l);
}

void	ft_press_key(char **line, int pos, int *error)
{
	char	str[5];
	int		l;
	int		fd;

	fd = dup(0);
	open_close_fd(0, fd);
	*line = (char *)malloc(sizeof(char) + 1);
	*line[0] = '\0';
	l = read_next_chr(fd, str, error);
	while (ft_strncmp(str, "\n", 1) != 0 && l > 0 && 
		!(pos == 0 && !ft_strncmp(str, "\x04", 1)) && *error == 0)
	{
		choise_keys(str, line, &pos);
		l = read_next_chr(fd, str, error);
	}
	open_close_fd(1, 0);
	if ((pos == 0 && !ft_strncmp(str, "\x04", 1)) || *error == 1)
		ft_free(line);
}
