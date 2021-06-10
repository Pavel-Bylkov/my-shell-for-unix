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


	i = 0;
	while (data->envp[i] && (ft_strncmp(data->envp[i], "PWD=",4)))
		i++;
	data->pwd_oldp->oldpwd_p = NULL;
	data->pwd_oldp->pwd_p = ft_strdup(&data->envp[i][4]);
}

void	init_data(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	data->index = (int *)malloc(sizeof(int) * (i));
	data->size = i;
	i = -1;
	while (env[++i] != NULL)
		data->envp[i] = ft_strdup(env[i]);
	data->envp[i] = NULL;

	create_index(&(*data));


	//data->index = (int *)malloc(sizeof(int) * data->size);

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
	return (0);
}

int		aam_main(t_data *data)
{
	//! ДАЕТ УТЕЧКУ - НАДО УБРАТЬ В ИНИЦИАЛИЗАЦИЮ!!!!
	data->pwd_oldp = (t_pwdpath *)malloc(sizeof(t_pwdpath));
	init_pwd_aam(data);
	sort_mass(data->envp, &data->index, data->size);
	//! ДО ЭТОГО МЕСТА

	ft_choice_command_aam(data);
	return (0);

}
