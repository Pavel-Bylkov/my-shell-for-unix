#include "my_shell.h"

static void		eof_exit(t_data *data)
{
	add_history("exit");
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	free_struct(data);
	write(1, "\e[2D   \e[2D", 11);
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

int		ft_readline(t_data *data)
{
	int error;

	error = 1;
	while (error == 1)
	{
		data->line = rl_gets_with_add_hist(SHELL_PROMT, &error);
		if (data->line == NULL)
			eof_exit(data);
		else if (data->line[0] == '\0')
			g_free(data->line);
		else
			error = quaote_open_mode(data);
		data->code_exit = error;
	}
	return (error);
}

void main_loop(t_data *data)
{
	int error;

	error = read_history(HISTORY_FILE); //! не использовать в финальной версии 	error = 0;
	while (1)
	{
		error = ft_readline(data);
		data->line = brackets_clean(data->line);
		error = parse_line(data, error);
		data->code_exit = run_comands(data, error);
		// print_pars(data);
		g_free((void *)data->line);
	    ft_parsclear(&(data->curr_pars));
		g_tmp_files_clear(&(data->tmp_files));
		data->count_files = 0;
	}
}
