#include "my_shell.h"

void		initialize_readline(void)
{
	rl_instream = stdin;
	rl_outstream = stderr;
	rl_readline_name = "Minishell";
	rl_initialize ();
}

static void		eof_exit(t_data *data)
{
	add_history("exit");
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	free_struct(data);
	write(1, "  \e[2D", 6);
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

int		ft_readline(t_data *data)
{
	int error;

	error = 0;
	data->line = NULL;
	initialize_readline();
	while (data->line == NULL)
	{
		data->line = rl_gets_with_add_hist(SHELL_PROMT);
		if (data->line == NULL)
			eof_exit(data);
		else if (data->line[0] == '\0')
		{
			g_free(data->line);
			data->line = NULL;
		}
		else
			error = quaote_open_mode(data);
	}
	return (error);
}

int 	count_redir(char *str)
{
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	while (str[++i[0]] != '\0')
	{
        if (ft_strncmp(&str[i[0]], "<<", 2) == 0 && backslash_is_active(str, i[0]) == 0
				&& quaote_is_open(str, i[0]) == 0)
			i[1]++;
	}
	return (i[1]);
}

void		count_pipes(t_data *data, int error)
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

void main_loop(t_data *data)
{
	int error;
	char **lines;
	int	i;

	error = read_history(HISTORY_FILE); //! не использовать в финальной версии 	error = 0;
	while (1)
	{
		error = ft_readline(data);
		data->line = brackets_clean(data->line);
		if (error == 0)
		{
			i = -1;
			lines = get_commands(data->line, ";");
			data->count_files = 0;
			while (lines[++i] != NULL)
			{
				data->count_files += count_redir(lines[i]);
				error = parse_line(lines[i], data, error);
				count_pipes(data, error);
				data->code_exit = run_comands(data, error);
				// print_pars(data);
				ft_parsclear(&(data->curr_pars));
				data->count_files += count_redir(lines[i]);
			}
			free_array((void **)lines);
		}
		g_free((void *)data->line);
		g_tmp_files_clear(&(data->tmp_files));
		data->count_files = 0;
	}
}
