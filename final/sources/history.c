#include "my_shell.h"

t_history		*new_history(char *str)
{
	t_history	*rez;

	rez = (t_history *)malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	rez->line = NULL;
	rez->next = NULL;
	rez->prev = NULL;
	ft_change_struct(&rez, str);
	return (rez);
}

void	history_add_front(t_history **lst, t_history *new)
{
	if (lst != NULL && new != NULL)
	{
		if (*lst != NULL)
		{
			new->next = *lst;
			new->next->prev = new;
		}
		*lst = new;
	}
}

void	ft_change_struct(t_history **list, char *s)
{
	if ((*list)->line != NULL)
		free((*list)->line);
	(*list)->line = ft_strdup(s);
}

void	ft_last_in_struct(t_history **list, char *str)
{
	while ((*list)->prev != NULL)
		*list = (*list)->prev;
	ft_change_struct(list, str);
}

void save_history(t_data *data)
{
    if (data->history->line[0] != '\0') //если последняя команда не пустая - записываем в файл истории
	{
		write(data->fd_hist, data->history->line, ft_strlen(data->history->line));
		write(data->fd_hist, "\n", 1);
	}
}

void				ft_historyclear(t_history **lst)
{
	t_history	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->line)
			free((*lst)->line);
		free((*lst));
		*lst = tmp;
	}
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
