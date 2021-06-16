#include <stdio.h>
#include "includes/my_shell.h"
#include <string.h>


void	temp_init_pars(t_pars *struc)  //! Временная функция
{
	struc->path = NULL;
	struc->argv = (char **)malloc(sizeof(char *) * 5);

	//struc->argv[0] = ft_strdup("export");
	//struc->argv[1] = ft_strdup("ddd'ddd");
	//struc->argv[2] = ft_strdup("tt");
	//struc->argv[3] = ft_strdup("tt=58");
	//struc->argv[4] = NULL;

	//struc->argv[0] = ft_strdup("unset");
	//struc->argv[1] = ft_strdup("4USER");
	//struc->argv[2] = ft_strdup("tt=58");
	//struc->argv[3] = ft_strdup("Apple_PubSub_Socket_Render");
	//struc->argv[4] = NULL;

	//struc->argv[0] = ft_strdup("env");
	//struc->argv[1] = ft_strdup("4USER");
	//struc->argv[2] = ft_strdup("tt=58");
	//struc->argv[3] = ft_strdup("Apple_PubSub_Socket_Render");
	//struc->argv[1] = NULL;

	//struc->argv[0] = ft_strdup("exit");
	//struc->argv[1] = ft_strdup("4");
	//struc->argv[2] = ft_strdup("58");
	//struc->argv[2] = NULL;

	//struc->argv[0] = ft_strdup("pwd");
	//struc->argv[1] = ft_strdup("--4");
	//struc->argv[2] = ft_strdup("58");
	//struc->argv[2] = NULL;

	struc->argv[0] = ft_strdup("cd");
	struc->argv[1] = ft_strdup("-");
	//struc->argv[1] = ft_strdup("/Users/aamarei/IRR");
	struc->argv[2] = NULL;

	//struc->argv[0] = ft_strdup("echo");
	//struc->argv[1] = ft_strdup("-n");
	//struc->argv[2] = ft_strdup("/Users/aamarei/IRR");
	//struc->argv[3] = ft_strdup("+++++++++\naamarei/IRR");
	//struc->argv[4] = NULL;


}

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

int		ft_redirect_aam(t_redir *red)
{
	int		fd_r;
	//int		fd_w;

	while (red)
	{
		if (red->f_spec[0] == '>' && red->f_spec[1] =='\0')
		{
			fd_r = open(red->out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("fd = %d", fd_r);
		}
		red = red->next;
	}
	return (fd_r);
}

int		ft_binar_command_aam(t_data *data, t_pars *pars)
{
	pid_t		pid;
	int			status;
	int			fd_r;
	int			fd_w;
	t_redir		*red;

	//fd[0] = 0;
	//fd[1] = 0;
printf("++++++++++++++ BINAR +++++++++++++++\n");
	fd_r = 0;
	fd_w = 0;
	red = pars->redirect;
	while (red)
	{
		if (red->f_spec[0] == '>' && red->f_spec[1] =='\0'){
			fd_r = open(red->out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("------------\n");
		}
		if (red->f_spec[0] == '<' && red->f_spec[1] =='\0')
		{
			fd_w = open(red->out, O_RDONLY);
	printf("==============\n");
		}
		red = red->next;
	}
	//	if (pars->redirect != NULL)
	//	{
	//		fd = ft_redirect_aam(pars->redirect);
	//printf("fd = %d\n", fd);
	//	}
	pid = fork();
	if (pid == 0)
	{

		if (fd_r > 2)
			dup2(fd_r, 1);
		if (fd_w > 2)
			dup2(fd_w, 0);
		execve(pars->path, pars->argv, data->envp);
		exit (-1);
	}
	waitpid(0, &status, 0);
	status = WEXITSTATUS(status);
	printf("status = %d\n", status);
	if (fd_r > 2)
		close(fd_r);
	if (fd_w > 2)
		close(fd_w);
printf("+++++++++ %d\n", fd_r);
	return (status);
}

int		ft_choice_command_aam(t_data *data)
{
	if (data->curr_pars->path == NULL)
	{
		if (!ft_strcmp(data->curr_pars->argv[0], "export"))
			ft_export(data, *data->curr_pars);
		else if (!ft_strcmp(data->curr_pars->argv[0], "unset"))
			ft_unset(data, *data->curr_pars);
		else if (!ft_strcmp(data->curr_pars->argv[0], "env"))
			ft_env(data, *data->curr_pars);
		else if (!ft_strcmp(data->curr_pars->argv[0], "exit"))
			ft_exit(*data->curr_pars);
		else if(!ft_strcmp(data->curr_pars->argv[0], "pwd"))
			ft_pwd();
		else if(!ft_strcmp(data->curr_pars->argv[0], "cd"))
			ft_cd(data, data->curr_pars);
		else if(!ft_strcmp(data->curr_pars->argv[0], "echo"))
			ft_echo(*data->curr_pars);
	}
	else
		return (ft_binar_command_aam(data, data->curr_pars));
	return (0);
}

int		aam_main(t_data *data)
{
	return (ft_choice_command_aam(data));
}
