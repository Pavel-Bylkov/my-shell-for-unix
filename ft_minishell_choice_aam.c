#include <stdio.h>
#include "my_shell.h"
#include <string.h>

int	ft_choice_command_aam(t_data *data)
{
	int			i;
	int			status;
	t_pars		*pars;

	pars = data->curr_pars;
	i = pars->count;
	if (pars->argv[0] == NULL)
		return (0);
	while (i-- > 0)
	{
		if (pars->path == NULL)
		{
			status = ft_choice_command_build(pars, data);
			if (status != 0)
				return (status);
		}
		else
			status = ft_binar_command_aam(data, pars);
		pars = pars->next;
	}
	return (ft_choice_command_waitpid(data->curr_pars->count));
}

int	ft_choice_command_waitpid(int j)
{
	int		status;

	while (j-- >= 0)
		waitpid(0, &status, 0);
	if (WTERMSIG(status) == 3)
	{
		write(2, "^\\Quit: 3\n", 10);
		return (131);
	}
	if (WTERMSIG(status) == 2)
	{
		//write(2, "^C\n", 3);
		return (130);
	}
	status = WEXITSTATUS(status);
	return (status);
}

int	ft_choice_command_build(t_pars *pars, t_data *data)
{
	int		status;
	int		fd_st[2];

	ft_redirect_aam(pars, data->fdesk);
	if (pars->count > 1)
		ft_choice_command_pipe(data, pars);
	else
	{
		ft_build_open_aam(data->fdesk, &fd_st[0], &fd_st[1]);
		status = ft_build_in_aam(data, pars);
		ft_build_close_aam(data->fdesk, &fd_st[0], &fd_st[1]);
		if (status != 0)
			return (status);
	}
	return (0);
}

void	ft_choice_command_pipe(t_data *data, t_pars *pars)
{
	pid_t		pid;
	int			fd_st[2];
	int			status;

	pipe(data->fdesk->fd[pars->count - 1]);
	pid = fork();
	if (pid == 0)
	{
		ft_pipe_open_aam(pars, data->fdesk);
		ft_build_open_aam(data->fdesk, &fd_st[0], &fd_st[1]);
		status = ft_build_in_aam(data, pars);
		exit(status);
	}
	ft_build_close_aam(data->fdesk, &fd_st[0], &fd_st[1]);
	ft_pipe_close_aam(pars, data->fdesk);
}
