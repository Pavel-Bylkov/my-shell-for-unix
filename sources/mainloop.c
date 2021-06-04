#include "my_shell.h"

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

int read_line(t_data *data)
{
    char *line;
    int pos;

    line = (char *)malloc(sizeof(char) + 1);
	line[0] = '\0';
    tputs(save_cursor, 1, ft_putchar);
    ft_press_key(data, &line, 0);
    ft_last_in_struct(&(data->history), line);
	ft_strcopy_fr(&line, data->history->line);
	tputs(restore_cursor, 1, ft_putchar);
    free(line);
	pos = ft_strlen(data->history->line);
	write(0, data->history->line, pos);
    write(1, "\n", 1);
    // Сохранение истории в файл .history / очистка памяти.
    save_history(data);
    return (0);
}
