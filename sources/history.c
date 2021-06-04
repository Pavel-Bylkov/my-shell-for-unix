#include "my_shell.h"

void			change_quaote_open(t_history **list)
{
	int		i;
	int		f[6]; // 0 - open' 1 - n*' 2 - open" 3 - n*"

	i = -1;
	ft_memset(f, 0, sizeof(f));
	ft_putendl_fd((*list)->quaotes, 1);
	while ((*list)->quaotes[++i] != '\0')
	{
		if ((*list)->quaotes[i] == '\'')
		{
			f[1] = (f[0] == 1) * f[1] + 1;
			f[0] = (f[2] == 0 && f[0] == 0) + !(f[2] == 0 && f[0] == 0) * f[0];
			f[4] = (f[1] == 3) + !(f[1] == 3) * f[4];
		}
		else
		{
			if (f[0] == 0 && f[2] == 0)
				f[2] = 1;
		}
	}
}

t_history		*new_history(char *str)
{
	t_history	*rez;

	rez = (t_history *)malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	rez->line = NULL;
	rez->quaotes = NULL;
	rez->quaote_open = 0;
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

void	change_quaotes(t_history **list, char *s)
{
	int		i[3];
	char	buff[1024];
	char	b2[1024];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	while (s[++i[0]] != '\0')
	{
		if (s[i[0]] == '\\')
			b2[++i[2]] = s[i[0]];
		else if (s[i[0]] == '\'' ||  s[i[0]] == '"')
		{
			while (i[2] > -1)
				buff[++i[1]] = b2[i[2]--];
			buff[++i[1]] = s[i[0]];
		}
		else if (i[0] > 0 && (s[i[0] - 1] == '\'' || s[i[0] - 1] == '"'))
			buff[++i[1]] = ' ';
		else
			i[2] = -1;
	}
	buff[++i[1]] = '\0';
	(*list)->quaotes = ft_strdup(buff);
}

void	ft_change_struct(t_history **list, char *s)
{
	if ((*list)->line != NULL)
		free((*list)->line);
	(*list)->line = ft_strdup(s);
	if ((*list)->quaotes != NULL)
		free((*list)->quaotes);
	change_quaotes(list, (*list)->line);
	change_quaote_open(list);
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
		if ((*lst)->quaotes)
			free((*lst)->quaotes);
		free((*lst));
		*lst = tmp;
	}
}
