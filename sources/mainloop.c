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
	write(1, "exit\n", 5);
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


int			how_is_how(char *str, int i)
{
	if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || 
				ft_strnchr(".*_@#$~!%%^[]{}:?-=+`/,", str[i]) != -1)
		return (5); 
	if (quaote_is_open(str, i) == 0 
			&& backslash_is_active(str, i) == 0)
	{
		if (str[i] == ' ')
			return (6);
		if (str[i] == ')' && brackets_is_open(str, i) < 0)
			return (7);
		if (str[i] == '(')
			return (8);
		if (str[i] == '>')
			return (9);
		if (str[i] == '<')
			return (10);
		return (ft_strnchr("|;&", str[i]));
	}
	return (3);
}

int		count_chr(char *str, char c, int n)
{
	int	i;
	int count;

	i = -1;
	count = 0;
	while (str[++i] && i <= n)
	{
		if (str[i] == c)
			count++;
		else
			count = 0;
	}
	return (count);
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
	int		flag;
	int		f[2];
	int		i;
	int		j;

	i = -1;
	flag = -1;
	while (str[++i])
	{
		flag = how_is_how(str, i);
		if (flag == 7)
			return (unexpected_token(")", 0));
		if (flag == 1 && str[i + 1] == ';' && str[i + 2] == '&')
			return (unexpected_token(";;&", 0));
		if (flag == 1 && str[i + 1] == ';')
			return (unexpected_token(";;", 0));
		if (flag >= 0 && flag <= 2)
		{
			j = i;
			f[0] = 0;
			while (--j > -1 && how_is_how(str, j) > 2)
			{
				if (how_is_how(str, j) == 5)
					f[0] = 1;
			}
			if (f[0] == 0 && count_chr(str, str[i], i) != 2)
				return (unexpected_token(ft_strdupn(&str[i], 
						1 + (ft_strnchr("|&", str[i + 1]) > -1)), 1));
		}
		// скобки (echo)
		if (flag == 8 && i - 1 > -1 && str[i - 1] != '<')
		{
			j = i;
			f[0] = 0;
			f[1] = 0;
			while (--j > -1 && how_is_how(str, j) > 2 && how_is_how(str, j) < 9)
			{
				if (how_is_how(str, j) == 5)
					f[0] = 1;
				else if (f[0] == 1 && how_is_how(str, j) == 6)
					f[1] = f[0]++;
			}
			if (f[0] == 1 && f[1] == 1)
				return (unexpected_token("(", 0));
			if ((f[0] == 1 && f[1] == 0) || (f[0] == 2 && f[1] == 1))
				return (unexpected_token(g_strdupanychr(&str[i + 1], ") "), 1));
		}
		// редиректы
		if (flag > 8)
		{
			j = i;
			f[0] = 1;
			while (--j > -1 && how_is_how(str, j) > 8)
				f[0]++;
			if (f[0] > 2)
				return (unexpected_token(ft_strdupn(&str[i], 1), 1));
		}
	}
	if (flag > 8)
		return (unexpected_token("newline", 0));
	return (0);
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
