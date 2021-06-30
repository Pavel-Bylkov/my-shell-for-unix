/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_and_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_and_run(t_data *data, int *error)
{
	int		i;
	char	**clines;

	if (*error == 0)
	{
		i = -1;
		clines = get_commands(data->line, ";");
		data->count_files = 0;
		while (clines[++i] != NULL)
		{
			data->count_files += count_redir(clines[i]);
			*error = parse_line(clines[i], data, *error);
			count_pipes(data, *error);
			data->code_exit = run_comands(data, *error);
			ft_parsclear(&(data->curr_pars));
			data->count_files += count_redir(clines[i]);
		}
		free_array((void **)clines);
	}
}
