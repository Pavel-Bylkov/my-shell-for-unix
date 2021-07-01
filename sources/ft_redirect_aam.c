#include "mshell.h"

int	ft_one_redir(t_redir *red, t_fdesk *fd)
{
	ft_open_file(&fd->fd_r, red, 1, 1);
	if (fd->fd_r < 0)
		return (ft_command_err_aam(red->out));
	return (0);
}

int	ft_back_redir(t_redir *red, t_fdesk *fd)
{
	ft_open_file(&fd->fd_w, red, 0, 2);
	if (fd->fd_w < 0)
	{
		ft_open_file(&fd->fd_r, red, 1, 0);
		return (ft_command_err_aam(red->out));
	}
	return (0);
}

int	ft_double_redir(t_redir *red, t_fdesk *fd)
{
	ft_open_file(&fd->fd_r, red, 1, 3);
	if (fd->fd_r < 0)
		return (ft_command_err_aam(red->out));
	return (0);
}

int	ft_redirect_aam(t_pars *pars, t_fdesk *fd)
{
	t_redir		*red;
	int			fl;

	fl = 0;
	red = pars->redirect;
	while (red && fl == 0)
	{
		if (red->f_spec[0] == '>' && red->f_spec[1] == '\0')
			fl = ft_one_redir(red, fd);
		else if (red->f_spec[0] == '<' && red->f_spec[1] == '\0')
			fl = ft_back_redir(red, fd);
		else if (red->f_spec[0] == '>' && red->f_spec[1] == '>')
			fl = ft_double_redir(red, fd);
		red = red->next;
	}
	return (fl);
}
