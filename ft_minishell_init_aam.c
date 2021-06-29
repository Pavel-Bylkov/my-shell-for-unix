/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_init_aam.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 09:56:51 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/29 09:56:52 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "my_shell.h"
#include <string.h>

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
	int		pos;

	i = -1;
	pos = -1;
	data->pwd_oldp = (t_pwdpath *)malloc(sizeof(t_pwdpath));
	data->pwd_oldp->oldpwd_p = NULL;
	data->pwd_oldp->pwd_p = NULL;
	while (data->envp[++i] && pos == -1)
		if (!ft_strncmp(data->envp[i], "PWD=", 3))
			pos = i;
	if (pos != -1)
		data->pwd_oldp->pwd_p = ft_strdup(&data->envp[pos][4]);
	i = -1;
	pos = -1;
	while (data->envp[++i] && pos == -1)
		if (!ft_strncmp(data->envp[i], "OLDPWD=", 6))
			pos = i;
	if (pos != -1)
		data->pwd_oldp->oldpwd_p = ft_strdup(&data->envp[pos][7]);
}

void	ft_shlvl_incr_add_aam(char **str)
{
	char	*new_str;
	char	*num;
	int		k;
	int		i;

	k = 0;
	i = 5;
	while ((*str)[++i] != '\0')
		k = 10 * k + (*str)[i] - 48;
	num = ft_itoa(k + 1);
	new_str = (char *)malloc(sizeof(char) * (7 + ft_strlen(num)));
	i = -1;
	while (++i < 6)
		new_str[i] = (*str)[i];
	while (i < (int)ft_strlen(num) + 6)
	{
		new_str[i] = num[i - 6];
		i++;
	}
	if (*str)
		free(*str);
	*str = ft_strdup(new_str);
	free(num);
	free(new_str);
}

void	init_data(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	data->index = NULL;
	data->size = i;
	i = -1;
	while (env[++i] != NULL)
	{
		data->envp[i] = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			ft_shlvl_incr_add_aam(&(data->envp[i]));
	}
	data->envp[i] = NULL;
	create_index(&(*data));
	sort_mass(data->envp, &data->index, data->size);
}

void	ft_init_fd_aam(t_data *data, t_fdesk **fd)
{
	int		i;

	(*fd)->fd = (int **)malloc(sizeof(int *) * (data->curr_pars->count + 1));
	i = 0;
	while (i < data->curr_pars->count)
	{
		(*fd)->fd[i] = (int *)malloc(sizeof(int) * 2);
		(*fd)->fd[i][0] = 0;
		(*fd)->fd[i][1] = 0;
		i++;
	}
	(*fd)->fd[i] = NULL;
	(*fd)->fd_r = 0;
	(*fd)->fd_w = 0;
	data->fdesk = *fd;
}
