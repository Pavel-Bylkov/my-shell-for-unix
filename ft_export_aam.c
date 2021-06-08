#include "includes/my_shell.h"


void	ft_out_export(t_data data)
{
	int		i;
	int		j;

	i = -1;
	printf("data.size = %d\n\n", data.size);
	while (++i < data.size)
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (data.envp[data.index[i]][j] !='\0')
		{
			if (data.envp[data.index[i]][j] == '=')
			{
				write(1, &(data.envp[data.index[i]][j++]), 1);
				write(1, "\"", 1);
			}
			if (data.envp[data.index[i]][j] != '\0')
				write(1, &(data.envp[data.index[i]][j++]), 1);
		}
		if (ft_char_in_str(data.envp[i], '=') != (int)ft_strlen(data.envp[i]))
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
}

char	**ft_free_mas(char **mas)
{
	int		i;

	i = 0;
	while (mas[i] != NULL)
		free(mas[i++]);
	free(mas);
	return (NULL);
}

char	*ft_env_work_add(char *line, char *str, int pos)
{
	char	*new_line;

	if (ft_strlen(line) == (size_t)pos)
		new_line = ft_strdup(str);
	else if (line[pos] == '=' && str[pos] == '=')
		new_line = ft_strdup(str);
	else
		new_line = ft_strdup(line);
	return (new_line);
}

char	**ft_env_add(t_data *data, char *str)
{
	char	**new_env;
	int		i;
	int		pos;

	new_env = (char **)malloc(sizeof(char *) * (data->size + 2));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	pos = ft_char_in_str(str, '=');
	while (data->envp[i])
	{
		new_env[i] = NULL;
		if (ft_strncmp(data->envp[i], str, pos) == 0)
		{
			new_env[i] = ft_env_work_add(data->envp[i], str, pos);
			break ;
		}
		new_env[i] = ft_strdup(data->envp[i]);
		i++;
	}
	if (i == data->size)
		new_env[data->size++] = ft_strdup(str);
	new_env[data->size] = NULL;
	ft_free_mas(data->envp);
	return (new_env);
}

void	ft_export_output_err(char *str)
{
	write(1, "my_shell: export: ", 18);
	write(1, "`", 1);
	write(1, str, ft_strlen(str));
	write(1, "': not a valid identifier\n", 26);
}
