/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_aam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 08:33:15 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/29 08:44:10 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int	ft_out_export_loop(t_data data, int i, int j, int *fl)
{
	if (data.envp[data.index[i]][j] == '=' && *fl == 0)
	{
		write(1, &(data.envp[data.index[i]][j++]), 1);
		write(1, "\"", 1);
		*fl = 1;
	}
	if (data.envp[data.index[i]][j] == '\\')
		write(1, "\\", 1);
	if (data.envp[data.index[i]][j] != '\0')
		write(1, &(data.envp[data.index[i]][j++]), 1);
	return (j);
}

void	ft_out_export(t_data data)
{
	int		i;
	int		j;
	int		fl;

	i = -1;
	while (++i < data.size)
	{
		fl = 0;
		j = 0;
		write(1, "declare -x ", 11);
		while (data.envp[data.index[i]][j] != '\0')
			j = ft_out_export_loop(data, i, j, &fl);
		if (ft_char_in_str(data.envp[i], '=') != (int)ft_strlen(data.envp[i]))
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
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

void	ft_env_add_loop(t_data *data, char ***new_env, char *str, int *flag)
{
	int		i;
	int		pos;

	i = 0;
	pos = ft_char_in_str(str, '=');
	while (data->envp[i])
	{
		(*new_env)[i] = NULL;
		if (ft_strncmp(data->envp[i], str, pos + 1) == 0)
		{
			(*new_env)[i] = ft_env_work_add(data->envp[i], str, pos);
			*flag = 1;
		}
		else
			(*new_env)[i] = ft_strdup(data->envp[i]);
		i++;
	}
}

char	**ft_env_add(t_data *data, char *str, int *size)
{
	char	**new_env;
	int		flag;

	flag = 0;
	new_env = (char **)malloc(sizeof(char *) * (data->size + 2));
	if (new_env == NULL)
		return (NULL);
	ft_env_add_loop(data, &new_env, str, &flag);
	if (flag == 0)
	{
		new_env[*size] = ft_strdup(str);
		*size = *size + 1;
	}
	new_env[*size] = NULL;
	ft_free_mas(data->envp);
	return (new_env);
}
