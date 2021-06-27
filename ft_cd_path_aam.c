#include "my_shell.h"

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

int	ft_path_back(t_data *data, char **path)
{
	int		pos;
	int		code;

	code = 0;
	pos = ft_pos_env_aam(data, "OLDPWD");
	*path = NULL;
	if (data->pwd_oldp->oldpwd_p != NULL)
	{
		if (pos == -1)
			*path = ft_strdup(data->pwd_oldp->oldpwd_p);
		else if (data->envp[pos][6] == '=')
			*path = ft_strdup(data->pwd_oldp->oldpwd_p);
		else if (data->envp[pos][6] == '\0')
		{
			*path = ft_strdup(data->pwd_oldp->pwd_p);
			code = ft_output_err_aam(1, " cd", ": OLDPWD not set\n", NULL);
		}
		write(1, *path, ft_strlen(*path));
		write(1, "\n", 1);
	}
	else
		code = ft_output_err_aam(1, " cd", ": OLDPWD not set\n", NULL);
	return (code);
}

int	ft_cd_path(t_data *data, char **path)
{
	int				code;
	struct stat		buff;

	code = chdir(*path);
	if (code == -1)
	{
		if (stat(*path, &buff) == 0)
			code = ft_output_err_aam(126, *path, ": Permission denied\n", NULL);
		else
			code = ft_output_err_aam(1, "cd: ", *path,
					": No such file or directory\n");
		free(*path);
		return (code);
	}
	else
	{
		free(*path);
		*path = getcwd(NULL, 0);
		ft_replace_oldpwd(data, *path);
	}
	return (code);
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
