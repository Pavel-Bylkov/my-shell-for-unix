#include "my_shell.h"

void        init_struct(t_data *data, char **envp)
{
    data->curr_pars = NULL;
	init_data(envp, data);
    data->history = NULL;
    data->fd_hist = -1;
    data->errors = NULL; //errors_create();
    load_history(data);
	data->insert_flag = 1;
}

void		load_history(t_data *data)
{
	char		*line;

	data->fd_hist = open(".history", O_CREAT | O_RDWR, 0666);
    if (data->fd_hist < 0)
        ft_exit_errcode(151, data);
    line = NULL;
    while (get_next_line(data->fd_hist, &line) > 0)
	{
		history_add_front(&(data->history), new_history(line));
		free(line);
		line = NULL;
	}
    if (line != NULL)
    {
		history_add_front(&(data->history), new_history(line));
		free(line);
	}
	history_add_front(&(data->history), new_history(""));
}
