/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whector <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/03/25 07:19:22 by whector          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAIN_FILE
#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		error;

	init_struct(&data, envp);
	error = 0;
	g_data = &data;
	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
		return (one_run(&data, argv[2]));
	else
		main_loop(&data);
	free_struct(&data);
	return (error);
}

int		one_run(t_data *data, char *str)
{
	int		error;

	error = 0;
	data->line = ft_strdup(str);
	if (data->line == NULL)
		return (0);
	if (check_unexpected_token(data->line) != 0)
		return (258);
	pars_and_run(data, &error);
	ft_free((void **)&(data->line));
	ft_tmp_files_clear(&(data->tmp_files));
	data->count_files = 0;
	free_struct(data);
	return (data->code_exit);
}
