#include "mshell.h"

int	ft_del_position(t_data data, char *str)
{
	int	i;
	int	len;
	int	pos;

	i = 0;
	pos = -1;
	len = ft_strlen(str);
	while (data.envp[i] != NULL && pos == -1)
	{
		if (ft_strncmp(data.envp[i], str, len) == 0
			&& (data.envp[i][len] == '=' || data.envp[i][len] == '\0'))
			pos = i;
		else
			i++;
	}
	return (pos);
}

char	**ft_env_del(t_data *data, char *str, int *size)
{
	char	**new_env;
	int		i;
	int		pos_del;

	pos_del = ft_del_position(*data, str);
	if (pos_del != -1)
	{
		new_env = (char **)malloc(sizeof(char *) * data->size);
		if (new_env == NULL)
			return (NULL);
		i = -1;
		while (++i < data->size - 1)
		{
			if (i < pos_del)
				new_env[i] = ft_strdup(data->envp[i]);
			else
				new_env[i] = ft_strdup(data->envp[i + 1]);
		}
		if (*size > 0)
			*size = *size - 1;
		new_env[*size] = NULL;
		ft_free_mas(data->envp);
		return (new_env);
	}
	return (data->envp);
}

void	ft_unset_output_err(char *str)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	write(2, "unset: ", 7);
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}
