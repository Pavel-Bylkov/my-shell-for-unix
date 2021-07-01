#include "mshell.h"

static void	eof_exit(t_data *data)
{
	ft_add_history("exit");
	free_struct(data);
	write(1, "  \e[2D", 6);
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

int	ft_readline(t_data *data)
{
	int		error;

	error = 0;
	while (data->line == NULL)
	{
		data->line = rl_gets_with_add_hist(SHELL_PROMT);
		if (data->line == NULL)
			eof_exit(data);
		else if (data->line[0] == '\0')
			ft_free((void **)&(data->line));
		else
			error = quaote_open_mode(data);
		if (error == 1 || error == 258)
			data->code_exit = error;
	}
	return (error);
}

int	count_redir(char *str)
{
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	while (str[++i[0]] != '\0')
	{
		if (ft_strncmp(&str[i[0]], "<<", 2) == 0
			&& backslash_is_active(str, i[0]) == 0
			&& quaote_is_open(str, i[0]) == 0)
			i[1]++;
	}
	return (i[1]);
}

void	count_pipes(t_data *data, int error)
{
	int		i;
	t_pars	*tmp;

	if (error != 0)
		return ;
	tmp = data->curr_pars;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->count == 1 && i == 0)
			tmp->counter = 1;
		else
			tmp->counter = ++i;
		if (tmp->count == 1)
			i = 0;
		tmp = tmp->next;
	}
}

void	main_loop(t_data *data)
{
	int		error;

	error = 0;
	load_history();
	while (1)
	{
		error = ft_readline(data);
		data->line = brackets_clean(data->line);
		pars_and_run(data, &error);
		ft_free((void **)&(data->line));
		ft_tmp_files_clear(&(data->tmp_files));
		data->count_files = 0;
	}
}
