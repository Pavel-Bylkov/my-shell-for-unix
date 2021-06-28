#include <stdio.h>
#include "my_shell.h"
#include <string.h>

int	ft_build_in_aam(t_data *data, t_pars *pars)
{
	if (!ft_strcmp(pars->argv[0], "export"))
		return (ft_export(data, pars));
	else if (!ft_strcmp(pars->argv[0], "unset"))
		return (ft_unset(data, *pars));
	else if (!ft_strcmp(pars->argv[0], "env"))
		return (ft_env(data, *pars));
	else if (!ft_strcmp(pars->argv[0], "exit"))
		return (ft_exit(*pars));
	else if (!ft_strcmp(pars->argv[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(pars->argv[0], "cd"))
		return (ft_cd(data, pars));
	else if (!ft_strcmp(pars->argv[0], "echo"))
		return (ft_echo(*pars));
	return (ft_output_err_aam(127, pars->argv[0],
					": No such file or directory\n", NULL));
}

void	ft_build_open_aam(t_fdesk *fd, int *fd_st0, int *fd_st1)
{
	if (fd->fd_r > 2)
	{
		*fd_st1 = dup(1);
		dup2(fd->fd_r, 1);
	}
	if (fd->fd_w > 2)
	{
		*fd_st0 = dup(0);
		dup2(fd->fd_w, 0);
	}
}

void	ft_build_close_aam(t_fdesk *fd, int *fd_st0, int *fd_st1)
{
	if (fd->fd_r > 2)
	{
		dup2(*fd_st1, 1);
		close(*fd_st1);
		close(fd->fd_r);
		fd->fd_r = 1;
	}
	if (fd->fd_w > 2)
	{
		dup2(*fd_st0, 0);
		close(*fd_st0);
		close(fd->fd_w);
		fd->fd_w = 0;
	}
}
