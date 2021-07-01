#include "mshell.h"

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

void	ft_key_backspace(char **line, int *pos)
{
	if (*pos > 0)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		*line = ft_del_symbol(*line, *pos);
		(*pos)--;
	}
}

void	ft_key_delete(char **line, int *pos)
{
	if (*pos > 0)
	{
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		*line = ft_del_symbol(*line, (*pos) + 1);
	}
}

void	ft_key_symbol(char **line, char *str, int *pos)
{
	tputs(tgetstr("im", 0), 1, ft_putchar);
	write(1, str, 1);
	tputs(tgetstr("ei", 0), 1, ft_putchar);
	*line = ft_add_symbol_str(*line, *str, *pos);
	(*pos)++;
}
