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

char	*ft_path_oneleft(t_data *data, char *path)
{
	int		len;
	char	*str;

	str = NULL;
	if ((ft_strlen(path) == 2 && path[1] == '.')
		|| (ft_strlen(path) == 3 && path[1] == '.' && path[2] == '/'))
	{
		len = (int)ft_strlen(data->pwd_oldp->pwd_p);
		if (len > 1)
		{
			while (data->pwd_oldp->pwd_p[len] != '/')
				len--;
			if (len > 1)
			{
				str = ft_strdup(data->pwd_oldp->pwd_p);
				str[len] = '\0';
			}
		}
	}
	else if (ft_strlen(path) == 2 && path[1] == '/')
		str = ft_strdup(data->pwd_oldp->pwd_p);
	free(path);
	return (str);
}

char	*ft_strjoin_path(char *str1, char *str2)
{
	char	*line;
	int		len;

	len = (int)ft_strlen(str1) + 1;
	line = ft_strjoin(str1, "/");
	line[len] = '\0';
	//if (str1)
	//	free(str1);
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

	if (pars->argv[1] == NULL || pars->argv[1][0] == '~')
		path = ft_path_home(data);
	else if (pars->argv[1] != NULL && pars->argv[1][0] == '-')
		path = ft_path_back(data);
	else
	{
		path = ft_strdup(pars->argv[1]);
		if (path)
		{
			if (path[0] == '.')
				path = ft_path_oneleft(data, path);
			else
				path = ft_strjoin_path(data->pwd_oldp->pwd_p, path);
		}

	}
	if (path)
	{
		er = chdir(path);
		if (er == -1)
			ft_cd_output_err(path, ": No such file or directory\n");
		else
			ft_replace_oldpwd(data, path);
		if (path)
			free(path);
	}
	return (0);
}
