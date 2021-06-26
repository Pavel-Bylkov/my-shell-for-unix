#include "my_shell.h"

void		int_handler(int status)
{
	if (status == SIGINT)
	{
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
		write(1, "\b\b", 2);
		write(1, "\n", 1);
		g_data->code_exit = 1;
	}
	if (status == SIGQUIT)
	{
		write(1, "\e[2D  \e[2D", 10);
	}
}

static void		eof_exit(t_data *data)
{
	add_history("exit");
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	free_struct(data);
	write(1, "\e[2D   \e[2D", 11);
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

char 		*rl_gets_with_add_hist(char *promt)
{
	char	*line;

	signal(SIGINT, int_handler);
	signal(SIGQUIT, int_handler);
	line = readline(promt);
	if (line && *line)
    	add_history(line);
	return (line);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int		ft_readline(t_data *data)
{
	int error;

	error = 0;
	data->line = rl_gets_with_add_hist(SHELL_PROMT);
	if (data->line == NULL)
		eof_exit(data);
	else if (data->line[0] == '\0')
	{
		g_free(data->line);
		error = 555;
	}
	else
		error = quaote_open_mode(data);
	return (error);
}

void main_loop(t_data *data)
{
	int error;

	error = read_history(HISTORY_FILE); //! не использовать в финальной версии 	error = 0;
	while (1)
	{
		error = ft_readline(data);
		if (error == 555)
			continue ;
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
