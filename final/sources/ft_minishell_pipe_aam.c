/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_pipe_aam.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 09:57:12 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/30 17:36:39 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_open_aam(t_pars *pars, t_fdesk *fd)
{
	if (fd->fd[pars->count])
		dup2(fd->fd[pars->count][0], 0);
	if (pars->count > 1)
		dup2(fd->fd[pars->count - 1][1], 1);
	if (fd->fd[pars->count])
	{
		close(fd->fd[pars->count][0]);
		fd->fd[pars->count][0] = 0;
		close(fd->fd[pars->count][1]);
		fd->fd[pars->count][1] = 1;
	}
	if (pars->count > 1)
	{
		close(fd->fd[pars->count - 1][0]);
		fd->fd[pars->count - 1][0] = 0;
		close(fd->fd[pars->count - 1][1]);
		fd->fd[pars->count - 1][1] = 1;
	}
}

void	ft_pipe_close_aam(t_pars *pars, t_fdesk *fd)
{
	if (pars->count > 0 && fd->fd[pars->count])
	{
		close(fd->fd[pars->count][0]);
		fd->fd[pars->count][0] = 0;
		close(fd->fd[pars->count][1]);
		fd->fd[pars->count][1] = 1;
	}
}

void	ft_binar_subsidiary_aam(t_data *data, t_pars *pars)
{
	int		code;

	ft_pipe_open_aam(pars, data->fdesk);
	code = ft_redirect_aam(pars, data->fdesk);
	if (code != 0)
		exit (code);
	if (data->fdesk->fd_r > 2)
		dup2(data->fdesk->fd_r, 1);
	if (data->fdesk->fd_w > 2)
		dup2(data->fdesk->fd_w, 0);
	code = execve(pars->path, pars->argv, data->envp);
	if (code < 0)
		code = ft_command_err_aam(pars->path);
	exit(code);
}

int	ft_binar_command_aam(t_data *data, t_pars *pars)
{
	pid_t		pid;
	int			code;

	code = 0;
	if (pars->count > 1)
		pipe(data->fdesk->fd[pars->count - 1]);
	pid = fork();
	if (pid == 0)
		ft_binar_subsidiary_aam(data, pars);
	ft_pipe_close_aam(pars, data->fdesk);
	ft_open_file(&(data->fdesk->fd_r), pars->redirect, 1, 0);
	ft_open_file(&(data->fdesk->fd_w), pars->redirect, 0, 0);
	return (code);
}
