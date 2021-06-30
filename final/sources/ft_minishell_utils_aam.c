/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_utils_aam.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 09:57:17 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/29 09:57:18 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_mass(char **mas, int *id[], int size)
{
	int		i;
	int		right;

	right = size - 1;
	while (right > 0)
	{
		i = 0;
		while (i < right)
		{
			if (ft_strcmp(mas[(*id)[i]], mas[(*id)[i + 1]]) > 0)
				ft_swap(&((*id)[i]), &((*id)[i + 1]));
			i++;
		}
		right--;
	}
}

void	ft_free_fd_aam(t_fdesk **fd)
{
	int		i;

	if ((*fd)->fd)
	{
		i = 0;
		while ((*fd)->fd[i])
			free((*fd)->fd[i++]);
		free((*fd)->fd);
	}
	if (*fd)
		free(*fd);
	*fd = NULL;
}

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_open_file(int *fd, t_redir *red, int k, int key)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = k;
	}
	if (key == 1)
		*fd = open(red->out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (key == 2)
		*fd = open(red->out, O_RDONLY);
	else if (key == 3)
		*fd = open(red->out, O_WRONLY | O_CREAT | O_APPEND, 0666);
}
