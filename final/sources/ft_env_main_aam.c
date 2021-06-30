/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_main_aam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 08:34:00 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/29 08:34:01 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_output(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->size)
	{
		if (!(ft_char_in_str(data->envp[i], '=')
				== (int)ft_strlen(data->envp[i])))
		{
			write(1, data->envp[i], ft_strlen(data->envp[i]));
			write(1, "\n", 1);
		}
	}
}

int	ft_env(t_data *data, t_pars pars)
{
	if (pars.argv[1] != NULL)
		return (ft_env_output_err(1, pars.argv[1]));
	else
		ft_env_output(data);
	return (0);
}
