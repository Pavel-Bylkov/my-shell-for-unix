#include "my_shell.h"

static void		int_handler(int status)
{
	if (status == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
}
static void		eof_exit(t_data *data)
{
	add_history("exit");
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	//free_struct(data);
	printf("exit\n");
	(void)data;
	exit(EXIT_SUCCESS);
}

int			is_endl_ignor(char *str)
{
	int		len;

	len = ft_strlen(str);
		// добавить <(  с закрытием  в конце строки)
			// сделать << "text" c закрытием  "text" в начале строки
	return (backslash_is_active(str, len) ||
			quaote_is_open(str, len) != 0 || str[len - 1] == '|'
				|| ft_strncmp(&str[len - 2], "&&", 2) == 0 ||
				brackets_is_open(str, len) > 0);
}

int		check_unexpected_token(char *str)
{
	// пустые команды, повторение редиректов, <( - c пробелом и не открытые скобки
	// ( - без разделения на команды
	(void)str;
	return (0);
}

static int		quaote_open_mode(t_data *data)
{
	int		len;
	char	*tmp;

	g_data->count_malloc += 1;
	len = ft_strlen(data->line);
	// отработать сброс при ошибках >>> или <<<< ||| ;; и т.п.
	if (check_unexpected_token(data->line) != 0)
		return (2);
	while (is_endl_ignor(data->line))
	{
		tmp = data->line;
		add_history(tmp); // добавить условие, что не включен режим <<
		if (ft_stdin_active(tmp))
			(void)tmp;
		data->line = readline(QUAOTE_PROMT);
		if (backslash_is_active(tmp, len))
		{
			if (NULL == data->line)
				exit(EXIT_SUCCESS);
			data->line = g_strjoin(tmp, -1, 0, data->line);
		}
		else if (NULL == data->line)
			return (print_err(2, data));
		else if (quaote_is_open(tmp, len) != 0)
			data->line = g_strjoin(tmp, 0, 1, data->line);
		else
			data->line = g_strjoin(tmp, 0, 0, data->line);
		g_data->count_malloc += 1;
	}
	add_history(data->line);
    write_history(HISTORY_FILE); //! не использовать в финальной версии
	return (0);
}

void main_loop(t_data *data)
{
    int error;

    error = read_history(HISTORY_FILE); //! не использовать в финальной версии (error = 0)
    signal(SIGINT, int_handler);
    while (1)
    {
        data->line = readline(SHELL_PROMT);
        if (data->line == NULL)
            eof_exit(data);
        else if (data->line[0] == '\0')
        {
            g_free(data->line);
            continue ;
        }
        else
            error = quaote_open_mode(data);
        error = parse_line(data, error);
        data->code_exit = run_comands(data, error);
        print_pars(data);
        g_free(data->line);
	    ft_parsclear(&(data->curr_pars));
		printf("count malloc = %d\n", data->count_malloc);
    }
}