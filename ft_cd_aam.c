#include "my_shell.h"

int	ft_pos_env_aam(t_data *data, char *str)
{
	int		i;
	int		pos;

	i = -1;
	pos = -1;
	while (data->envp[++i] && pos == -1)
	{
		if (!ft_strncmp(data->envp[i], str, ft_strlen(str))
			&& (data->envp[i][(int)ft_strlen(str)] == '='
			|| data->envp[i][(int)ft_strlen(str)] == '\0'))
			pos = i;
	}
	return (pos);
}

void	ft_replace_one(t_data *data, int pos)
{
	char	*str;

	if (data->envp[pos][6] == '\0' || data->envp[pos][6] == '=')
	{
		str = ft_strjoin("OLDPWD=", data->pwd_oldp->oldpwd_p);
		free(data->envp[pos]);
		data->envp[pos] = ft_strdup(str);
		free(str);
	}
}

void	ft_replace_two(t_data *data, int pos)
{
	char	*str;

	if (data->envp[pos][3] == '\0' || data->envp[pos][3] == '=')
	{
		str = ft_strjoin("PWD=", data->pwd_oldp->pwd_p);
		free(data->envp[pos]);
		data->envp[pos] = ft_strdup(str);
		free(str);
	}
}

void	ft_replace_oldpwd(t_data *data, char *path)
{
	int		pos;

	if (data->pwd_oldp->oldpwd_p)
		free(data->pwd_oldp->oldpwd_p);
	data->pwd_oldp->oldpwd_p = ft_strdup(data->pwd_oldp->pwd_p);
	if (path)
	{
		free(data->pwd_oldp->pwd_p);
		data->pwd_oldp->pwd_p = ft_strdup(path);
	}
	pos = ft_pos_env_aam(data, "OLDPWD");
	if (pos != -1)
		ft_replace_one(data, pos);
	pos = ft_pos_env_aam(data, "PWD");
	if (pos != -1)
		ft_replace_two(data, pos);
}
