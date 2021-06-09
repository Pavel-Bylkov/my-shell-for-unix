#include "my_shell.h"

void	ft_cd_output_err(char *str1, char *str2)
{
	write(1, "my_shell: cd: ", 14);
	write(1, str1, ft_strlen(str1));
	write(1, str2, ft_strlen(str2));
}

char	*ft_path_home(t_data *data)
{
	int		i;
	int		pos;
	char	*str;

	str = NULL;
	pos = -1;
	i = -1;
	while (data->envp[++i] != NULL && pos == -1)
		if (!ft_strncmp(data->envp[i], "HOME", 4)
			&& (data->envp[i][4] == '=' || data->envp[i][4] == '\0'))
			pos = i;
	if (pos > -1)
	{
		if (data->envp[pos][4] == '=' && data->envp[pos][5] != '\0')
			str = ft_strdup(&data->envp[pos][5]);
		else
			str = NULL;
	}
	return (str);
}

char	*ft_path_back(t_data *data)
{
	int		i;
	char	*str;
	int		pos;

	i = 0;
	pos = ft_pos_env_aam(data, "OLDPWD");
	str = NULL;
	if (pos != -1)
	{
		if (data->envp[i][6] == '=' && data->envp[i][7] != '\0')
		{
			str = ft_strdup(&data->envp[i][7]);
			ft_replace_oldpwd(data, str);
		}
		else if (data->envp[i][6] == '\0')
		{
			ft_cd_output_err(NULL, "OLDPWD not set\n");
			ft_replace_oldpwd(data, NULL);
		}
	}
	else
		ft_cd_output_err(NULL, "OLDPWD not set\n");
	return (str);
}

int	ft_cd(t_data *data, t_pars *pars)
{
	int		er;
	char	*path;

	if (pars->argv[1] == NULL || pars->argv[1][0] == '~')
		path = ft_path_home(data);
	else if (pars->argv[1] != NULL && pars->argv[1][0] == '-')
		path = ft_path_back(data);
	else
		path = ft_strdup(pars->argv[1]);
	if (path)
	{
		er = chdir(path);
		if (er == -1)
			ft_cd_output_err(path, ": No such file or directory\n");
		if (path != NULL)
			free(path);
	}
	return (0);
}
