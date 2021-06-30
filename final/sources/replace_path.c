/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/06/30 10:14:20 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	return (ft_strncmp(str, "echo", 5) == 0
		|| ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "pwd", 4) == 0
		|| ft_strncmp(str, "export", 7) == 0
		|| ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "exit", 5) == 0);
}

char	*get_path(t_data *data)
{
	char	*path;
	int		i;

	path = NULL;
	if (data->envp)
	{
		i = -1;
		while (data->envp[++i] != NULL)
			if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
				path = data->envp[i];
	}
	return (path);
}

char	*get_abs_path(char	*abs_path, char *path, char *name, int *flag)
{
	int		i[2];
	int		fd;

	i[0] = 5;
	*flag = 0;
	while (path[i[0]] && *flag == 0)
	{
		i[1] = i[0];
		while (path[i[1]] != '\0' && path[i[1]] != ':')
			i[1]++;
		abs_path = ft_newpath(&path[i[0]], i[1] - i[0], name);
		fd = open(abs_path, O_RDONLY);
		if (fd > 0)
		{
			*flag = 1;
			close(fd);
		}
		else
			ft_free((void **)&abs_path);
		i[0] = i[1] + (path[i[1]] == ':') * 1;
	}
	return (abs_path);
}

char	*search_in_path(t_data *data, char *name)
{
	char	*path;
	char	*abs_path;
	int		flag;

	path = get_path(data);
	if (path)
	{
		abs_path = get_abs_path(NULL, path, name, &flag);
		if (flag)
		{
			ft_free((void **)&name);
			return (abs_path);
		}
	}
	return (name);
}

void	find_path(t_data *data, t_pars *tmp)
{
	int		len;
	char	*name;

	name = tmp->argv[0];
	if (!name)
		return ;
	if (!is_builtin(name) && chr_in_str('/', name) == -1
		&& ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0)
		tmp->argv[0] = search_in_path(data, name);
	if (chr_in_str('/', tmp->argv[0]) > -1)
	{
		tmp->path = tmp->argv[0];
		len = ft_strlen(tmp->path);
		while (tmp->path[len - 1] != '/')
			len--;
		tmp->argv[0] = ft_strdup(&(tmp->path[len]));
	}
}
