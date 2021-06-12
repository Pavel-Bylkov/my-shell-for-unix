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
	char	*str;
	int		pos;

	pos = ft_pos_env_aam(data, "OLDPWD");
	str = NULL;
	if (data->pwd_oldp->oldpwd_p != NULL)
	{
		if (pos == -1)
			str = ft_strdup(data->pwd_oldp->oldpwd_p);
		else if (data->envp[pos][6] == '=')
			str = ft_strdup(data->pwd_oldp->oldpwd_p);
		else if (data->envp[pos][6] == '\0')
		{
			ft_cd_output_err(NULL, "OLDPWD not set\n");
			str = ft_strdup(data->pwd_oldp->pwd_p);
		}
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	else
		ft_cd_output_err(NULL, "OLDPWD not set\n");
	return (str);
}

char	*ft_strjoin_path(char *str1, char *str2)
{
	char	*line;
	int		len;

	len = (int)ft_strlen(str1) + 1;
	line = ft_strjoin(str1, "/");
	line[len] = '\0';
	len = len + (int)ft_strlen(str2);
	str1 = ft_strjoin(line, str2);
	if (str2)
		free(str2);
	free(line);
	return (str1);
}

int	ft_cd(t_data *data, t_pars *pars)
{
	int		er;
	char	*path;

	path = NULL;
	if (pars->argv[1] == NULL)
		path = ft_path_home(data);
	else
	{
		if (pars->argv[1][0] == '~' && pars->argv[1][1] == '\0')
			path = ft_path_home(data);
		else if (pars->argv[1][0] == '~' && pars->argv[1][1] == '\0')
			ft_cd_output_err(pars->argv[1], ": No such file or directory\n");
		else if (pars->argv[1] != NULL && pars->argv[1][0] == '-' && ft_strlen(pars->argv[1]) == 1)
			path = ft_path_back(data);
		else if (pars->argv[1][0] == '-' && pars->argv[1][1] != '\0')
			ft_cd_output_err(pars->argv[1], ": No such file or directory\n");
		else
			path = ft_strdup(pars->argv[1]);
	}
	if (path)
	{
		er = chdir(path);
		if (er == -1)
			ft_cd_output_err(pars->argv[1], ": No such file or directory\n");
		else
		{
			path = getcwd(NULL, 0);
			ft_replace_oldpwd(data, path);
		}
	}
	if (path)
		free(path);
	return (0);
}
