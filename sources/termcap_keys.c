#include "my_shell.h"

void	ft_key_up(t_history **hist, char **line, int *pos)
{
	if ((*hist)->next != NULL)
	{
		(*hist) = (*hist)->next;
		ft_strcopy_fr(line, (*hist)->line);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		*pos = ft_strlen((*hist)->line);
		write(0, (*hist)->line, *pos);
	}
}

void	ft_key_down(t_history **hist, char **line, int *pos)
{
	if ((*hist)->prev != NULL)
	{
		(*hist) = (*hist)->prev;
		ft_strcopy_fr(line, (*hist)->line);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		*pos = ft_strlen((*hist)->line);
		write(0, (*hist)->line, *pos);
	}
}

void	ft_key_left(int *pos)
{
	if (*pos > 0)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		(*pos)--;
	}
}

void	ft_key_right(char *line, int *pos)
{
	if (*pos < (int)ft_strlen(line))
	{
		tputs(tgetstr("nd", 0), 1, ft_putchar);
		(*pos)++;
	}
}

void	ft_key_backspace(t_history **hist, char **line, int *pos)
{
	if (*pos > 0)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		*line = ft_del_symbol(*line, *pos);
		ft_change_struct(hist, *line);
		(*pos)--;
	}
}