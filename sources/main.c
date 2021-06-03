#include "my_shell.h"

int main(int argc, char **argv, char **envp)
{
    t_data data;
    int error;

    (void)argc;
    (void)argv;
    // Загрузка файлов конфигурации.
    init_struct(&data, envp);
    load_history(&data);

    // Запуск цикла команд.
    error = main_loop(&data);

    close(data.fd_hist);
    free_struct(&data);

    return (error);
}

void                init_struct(t_data *data, char **envp)
{
    data->curr_pars = NULL;
    data->envp = copy_str_array(envp);
    data->history = NULL;
    data->fd_hist = -1;
    data->errors = errors_create();
}

void                load_history(t_data *data)
{
    int			res;
	int			len;
	char		*line;

	data->fd_hist = open("histoty_command.txt", O_CREAT | O_RDWR, 0666);  //! Надо будет закрыть файл при выходе из минишела
	res = get_next_line(data->fd_hist, &line);
	while (res == 1)
	{
		len = ft_strlen(line);
		if (data->history == NULL)
			ft_new_list(&(data->history), line, len);
		else
			ft_add_list(&(data->history), line, len);
		free(line);
		res = get_next_line(data->fd_hist, &line);
	}
	if (res != 0)
	{
		if (data->history == NULL)
			ft_new_list(&(data->history), line, len);
		else
			ft_add_list(&(data->history), line, len);
	}
	free(line);
	ft_add_list(&(data->history), "", 0);

}

void save_history(t_data *data)
{
    if (data->history->line[0] != '\0') //если последняя команда не пустая - записываем в файл истории
	{
		write(data->fd_hist, data->history->line, ft_strlen(data->history->line));
		write(data->fd_hist, "\n", 1);
	}
}

int main_loop(t_data *data)
{
    int error;
    struct termios term;
	char	*term_name;

	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &=~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
    while (1)
    {
        ft_putstr_fd("my_shell>$ ", 1);
        error = read_line(data);
        error = parse_line(data);
        error = run_comands(data);
        error = free_tmp_data(data);
        if (error != 0)
            return (error);
    }
}

int run_comands(t_data *data)
{
    (void)data;
    return (0);
}

int free_tmp_data(t_data *data)
{
    (void)data;
    return (0);
}

void free_struct(t_data *data)
{
    (void)data;
}