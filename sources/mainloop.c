#include "my_shell.h"

void		int_handler(int status)
{
	if (status == SIGINT)
	{
		write(1, "\e[2D  ", 6); //[nD — перемещает курсор по строке влево на п позиций.
		write(1, "\n", 1); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
		g_data->code_exit = 130;
	}
}

void		int_handler2(int status)
{
	if (status == SIGINT)
	{
		write(1, "\e[2D  ", 6);
		rl_on_new_line();
		rl_replace_line("  ", 0); // Clear the previous text
		write(1, "\n", 1); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
		// придумать как прервать readline
		g_data->code_exit = 130;
	}
}
static void		eof_exit(t_data *data)
{
	add_history("exit");
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	//free_struct(data);
	//write(1, "\b", 1);
	//rl_replace_line("", 0); // Clear the previous text
	//rl_redisplay();
	write(1, "exit\n", 5);
	(void)data;
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

char 		*rl_gets_without_hist(char *promt)
{
	char	*line;

	signal(SIGINT, int_handler2);
	line = readline(promt);
	return (line);
}

int			is_endl_ignor(char *str, t_data *data)
{
	int		len;

	len = ft_strlen(str);
		// добавить <(  с закрытием  в конце строки)
			// сделать << "text" c закрытием  "text" в начале строки
	return (backslash_is_active(str, len) ||
			quaote_is_open(str, len) != 0 || str[len - 1] == '|'
				|| ft_strncmp(&str[len - 2], "&&", 2) == 0 ||
				brackets_is_open(str, len) > 0 || ft_stdin_active(str, data));
}
// add check echo ${USER HOME}
// bash: ${USER HOME}: bad substitution
int		check_unexpected_token(char *str)
{
	// пустые команды, повторение редиректов, <( - c пробелом и не открытые скобки
	// отработать сброс при ошибках >>> или <<<< ||| ;; |;& и т.п.
	// ( - без разделения на команды
	// <<\n - unexpected token `newline'
	// проверить на спец символы ! - нужно ли выдавать ошибку
	(void)str;
	return (0);
}

static int		quaote_open_mode(t_data *data)
{
	int		len;
	char	*tmp;
	int		error;

	g_data->count_malloc += 1;
	len = ft_strlen(data->line);
	error = 0;
	if (check_unexpected_token(data->line) != 0)
		return (2);
	while (is_endl_ignor(data->line, data) && error == 0)
	{
		tmp = data->line;
		if (backslash_is_active(tmp, len))
		{
			data->line = rl_gets_without_hist(QUAOTE_PROMT);
			if (NULL == data->line)
				exit(0); //ft_perr(g_strdupn(tmp, ft_strlen(tmp) - 1),
						//127, NULL, "command not found")
			data->line = g_strjoin(tmp, -1, 0, data->line);
			g_data->count_malloc += 1;
			add_history(data->line);
		}
		 // добавить условие, что не включен режим <<
		else if (ft_stdin_active(tmp, data))
			error = read_tmp_stdin(data, tmp);
		// если скобка - подставить ; и убрать \n
		else
		{
			data->line = rl_gets_without_hist(QUAOTE_PROMT);
			if (NULL == data->line)
				return (unexpected_eof(tmp));
			else if (quaote_is_open(tmp, len) != 0)
				data->line = g_strjoin(tmp, 0, 1, data->line);
			else
				data->line = g_strjoin(tmp, 0, 0, data->line);
			g_data->count_malloc += 1;
			add_history(data->line);
		}
		len = ft_strlen(data->line);
	}
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	return (error);
}

int		ft_readline(t_data *data)
{
	int error;

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
		else if (error == 2)
			ft_perr("syntax error", 2, NULL, "unexpected end of file");
        error = parse_line(data, error);
        data->code_exit = run_comands(data, error);
        //print_pars(data);
        g_free((void *)data->line);
	    ft_parsclear(&(data->curr_pars));
		g_tmp_files_clear(&(data->tmp_files));
		data->count_files = 0;
		printf("count malloc = %d\n", data->count_malloc);
    }
}
