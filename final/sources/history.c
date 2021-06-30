/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/06/30 17:34:35 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_history(char *str)
{
	int		fd_hist;

	fd_hist = open(".history", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_hist > 0)
	{
		ft_putendl_fd(str, fd_hist);
		close(fd_hist);
	}
	add_history(str);
}

void	load_history(void)
{
	int		fd_hist;
	char	*line;

	fd_hist = open(".history", O_RDONLY);
	if (fd_hist < 0)
		return ;
	line = NULL;
	while (get_next_line(fd_hist, &line) > 0)
	{
		add_history(line);
		free(line);
	}
	if (line != NULL)
		free(line);
	close(fd_hist);
}
