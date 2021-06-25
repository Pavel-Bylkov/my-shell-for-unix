#include "my_shell.h"

void		int_handler(int status)
{
	if (status == SIGINT)
	{
		// while (write(1, "\e[1С", 4));
		// write(1, "\e[2D", 4); //[nD — перемещает курсор по строке влево на п позиций.
		// write(1, "  \n", 3); // Move to a new line
		//rl_replace_line("\e[2D    ", 0); // Clear the previous text
		write(1, "\n", 1);
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
		g_data->code_exit = 1;
	}
}

static void		eof_exit(t_data *data)
{
	add_history("exit");
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	free_struct(data);
	write(1, "exit\n", 20);
	exit(EXIT_SUCCESS);
}

char 		*rl_gets_with_add_hist(char *promt)
{
	char	*line;

	signal(SIGINT, int_handler);
	line = readline(promt);
	if (line && *line)
    	add_history(line);
	return (line);
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
		error = parse_line(data, error);
		data->code_exit = run_comands(data, error);
		//print_pars(data);
		g_free((void *)data->line);
	    ft_parsclear(&(data->curr_pars));
		g_tmp_files_clear(&(data->tmp_files));
		data->count_files = 0;
	}
}
