#include <stdio.h>
#include "includes/my_shell.h"
#include <string.h>

void	create_index(t_data *data)
{
	int		i;

	if (data->index != NULL)
		free(data->index);
	data->index = (int *)malloc(sizeof(int) * (data->size));
	i = -1;
	while (++i < data->size)
		data->index[i] = i;
}

void	init_pwd_aam(t_data *data)
{
	int		i;
	int		pos;

	i = -1;
	pos = -1;
	data->pwd_oldp = (t_pwdpath *)malloc(sizeof(t_pwdpath));
	data->pwd_oldp->oldpwd_p = NULL;
	data->pwd_oldp->pwd_p = NULL;
	while (data->envp[++i] && pos == -1)
		if (!ft_strncmp(data->envp[i], "PWD=", 3))
			pos = i;
	if (pos != -1)
		data->pwd_oldp->pwd_p = ft_strdup(&data->envp[pos][4]);
	i = -1;
	pos = -1;
	while (data->envp[++i] && pos == -1)
		if (!ft_strncmp(data->envp[i], "OLDPWD=", 6))
			pos = i;
	if (pos != -1)
		data->pwd_oldp->oldpwd_p = ft_strdup(&data->envp[pos][7]);
}

void	init_data(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	data->index = NULL;
	data->size = i;
	i = -1;
	while (env[++i] != NULL)
		data->envp[i] = ft_strdup(env[i]);
	data->envp[i] = NULL;

	create_index(&(*data));
	sort_mass(data->envp, &data->index, data->size);
}

void	swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

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
				swap(&((*id)[i]), &((*id)[i + 1]));
			i++;
		}
		right--;
	}
}

int		ft_redirect_aam(t_pars *pars, t_fdesk *fd)
{
	t_redir		*red;

	red = pars->redirect;

	while (red)
	{
		if (red->f_spec[0] == '>' && red->f_spec[1] =='\0')
			fd->fd_r = open(red->out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (red->f_spec[0] == '<' && red->f_spec[1] =='\0')
			fd->fd_w = open(red->out, O_RDONLY);
		if (red->f_spec[0] == '>' && red->f_spec[1] =='>')
			fd->fd_r = open(red->out, O_WRONLY | O_CREAT | O_APPEND, 0666);
		red = red->next;
	}
	return (0);
}

void	ft_pipe_open_aam(t_pars *pars, t_fdesk *fd)
{
	if (fd->fd[pars->count])
		dup2(fd->fd[pars->count][0], 0);
	if (pars->count > 1)
		dup2(fd->fd[pars->count - 1][1], 1);
	if (fd->fd[pars->count])
	{
		close(fd->fd[pars->count][0]);
		close(fd->fd[pars->count][1]);
	}
	if (pars->count > 1)
	{
		close(fd->fd[pars->count - 1][0]);
		close(fd->fd[pars->count - 1][1]);
	}
}

void	ft_pipe_close_aam(t_pars *pars, t_fdesk *fd)
{
	if (pars->count > 0 && fd->fd[pars->count])
	{
		close(fd->fd[pars->count][0]);
		close(fd->fd[pars->count][1]);
	}
}



int		ft_binar_command_aam(t_data *data, t_pars *pars)
{
	pid_t		pid;
	int			code;

	ft_redirect_aam(pars, data->fdesk);
	if (pars->count > 1)
		pipe(data->fdesk->fd[pars->count - 1]);
	pid = fork();
	if (pid == 0)
	{
		ft_pipe_open_aam(pars, data->fdesk);

		if (data->fdesk->fd_r > 2)
			dup2(data->fdesk->fd_r, 1);
		if (data->fdesk->fd_w > 2)
			dup2(data->fdesk->fd_w, 0);
		code = execve(pars->path, pars->argv, data->envp);
		if (code < 0)
			code = ft_command_err_aam(pars->path);
		exit (code);
	}

	if (data->fdesk->fd_r > 2)
		close(data->fdesk->fd_r);
	if (data->fdesk->fd_w > 2)
		close(data->fdesk->fd_w);
	ft_pipe_close_aam(pars, data->fdesk);
	return (0);
}

int	ft_output_err_aam(int code, char *str1, char *str2, char *str3)
{
	write(2, "my_shell: ", 10);
	if (str1)
		write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	return (code);
}

int	ft_command_err_aam(char *name_f)
{
	struct stat	buff;
	int			code;
	//DIR			dir_t;

	code = 0;
	if (ft_char_in_str(name_f, '/') < (int)ft_strlen(name_f))
	{
		if (opendir(name_f) != NULL)
			return (ft_output_err_aam(126, name_f, ": is a directory\n", NULL));
		else
			return (ft_output_err_aam(127, name_f, ": No such file or directory\n", NULL));
	}
	code = stat(name_f, &buff);
	if (code < 0)
		return (ft_output_err_aam(127, name_f, ": command not found\n", NULL));
	else
		printf("OK!!!\n");

	return (code);
}

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
		else if(!ft_strcmp(pars->argv[0], "pwd"))
			return (ft_pwd());
		else if(!ft_strcmp(pars->argv[0], "cd"))
			return (ft_cd(data, pars));
		else if(!ft_strcmp(pars->argv[0], "echo"))
			return (ft_echo(*pars));
	return (ft_command_err_aam(pars->argv[0]));
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
	}
	if (fd->fd_w > 2)
	{
		dup2(*fd_st0, 0);
		close(*fd_st0);
		close(fd->fd_w);
	}
}

int	ft_choice_command_aam(t_data *data)
{
	int			fd_st[2];
	int			i;
	int			j;
	int			status;
	t_pars		*pars;
	pid_t		pid;

	pars = data->curr_pars;
	i = pars->count;
	j = i;
	while (i-- > 0)
	{
		if (pars->path == NULL)
		{
			ft_redirect_aam(pars, data->fdesk);
			if (pars->count > 1)
			{
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
			else
			{
				ft_build_open_aam(data->fdesk, &fd_st[0], &fd_st[1]);
				status = ft_build_in_aam(data, pars);
				ft_build_close_aam(data->fdesk, &fd_st[0], &fd_st[1]);
				if (status != 0)
					return (status);
			}
		}
		else
		{
			status = ft_binar_command_aam(data, pars);
			if (status < 0)
				return (ft_command_err_aam(pars->path));
		}

		pars = pars->next;
	}
	while (j-- > 0)
		waitpid(0, &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}

void	ft_init_fd_aam(t_data *data, t_fdesk **fd)
{
	int		i;

	(*fd)->fd = (int **)malloc(sizeof(int *) * (data->curr_pars->count + 1));
	i = 0;
	while (i < data->curr_pars->count)
	{
		(*fd)->fd[i] = (int *)malloc(sizeof(int) * 2);
		(*fd)->fd[i][0] = 0;
		(*fd)->fd[i][1] = 0;
		i++;
	}
	(*fd)->fd[i] = NULL;
	(*fd)->fd_r = 0;
	(*fd)->fd_w = 0;
	data->fdesk = *fd;
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
		free (*fd);
	*fd = NULL;
}

int		aam_main(t_data *dt)
{
	int			ret;
	t_fdesk		*fd;
	t_pars		*pars;
	t_data		*data;




	data = dt;
	pars = data->curr_pars;
	while (data->curr_pars)
	{
		fd = (t_fdesk *)malloc(sizeof(t_fdesk));
		ft_init_fd_aam(data, &fd);
		ret = ft_choice_command_aam(data);
	//printf("ret = %d\n", ret);
		while (data->curr_pars->count > 1)
			data->curr_pars = data->curr_pars->next;
		if (data->curr_pars->f_spec[0] == ';')
			data->curr_pars = data->curr_pars->next;
		else if (data->curr_pars->f_spec[0] == '&' && data->curr_pars->f_spec[1] == '&')
		{
			if (ret == 0)
				data->curr_pars = data->curr_pars->next;
			else
			{
				while (data->curr_pars->f_spec[0] != ';'
					&& !(data->curr_pars->f_spec[0] == '|' && data->curr_pars->f_spec[1] == '|')
					&& data->curr_pars->next)
					data->curr_pars = data->curr_pars->next;
				if (data->curr_pars)
					data->curr_pars = data->curr_pars->next;
			}
		}
		else if (data->curr_pars->f_spec[0] == '|' && data->curr_pars->f_spec[1] == '|')
		{
			if (ret != 0)
				data->curr_pars = data->curr_pars->next;
			else
			{
				while (data->curr_pars->f_spec[0] != ';' && data->curr_pars->f_spec[0] != '&'
					//&& !(data->curr_pars->f_spec[0] == '|' && data->curr_pars->f_spec[1] == '\0')
					&& data->curr_pars->next)
					data->curr_pars = data->curr_pars->next;
				if (data->curr_pars)
					data->curr_pars = data->curr_pars->next;
			}
		}
		else
			data->curr_pars = data->curr_pars->next;
//printf("%p\n", fd);
		ft_free_fd_aam(&fd);
//printf("%p\n", fd);

	}
	if (fd)
		ft_free_fd_aam(&fd);
	data->curr_pars = pars;
//printf("ret = %d\n", ret);
	return (ret);
}
