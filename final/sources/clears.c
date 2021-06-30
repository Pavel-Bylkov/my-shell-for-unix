/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clears.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/06/30 09:51:11 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(void **s)
{
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != NULL)
			ft_free((void **)&s[i++]);
		ft_free((void **)&s);
	}
}

void	free_struct(t_data *data)
{
	ft_parsclear(&(data->curr_pars));
	free_array((void **)data->envp);
	ft_free((void **)&data->line);
	ft_free((void **)&data->index);
}

void	ft_free(void **content)
{
	if (*content != NULL)
	{
		free(*content);
		*content = NULL;
	}
}
