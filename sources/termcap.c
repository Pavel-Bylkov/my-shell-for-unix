#include "my_shell.h"

#include <string.h>
#include <stdio.h>


char	*ft_del_symbol(char *str, int i) //? Удаление i-го символа
{
	char	*s;
	int		k;

	k = ft_strlen(str);
	s = (char *)malloc(sizeof(char) * k);
	k = 0;
	while (k < i - 1)
	{
		s[k] = str[k];
		k++;
	}
	while (str[k + 1] != '\0')
	{
		s[k] = str[k + 1];
		k++;
	}
	s[k] = '\0';
	free(str);
	return (s);
}

char	*ft_add_symbol_str(char *str, char c, int i) //? Вставка символа c в строку str после i-го символа
{
	char	*s;
	int		len;
	int		k;

	len = ft_strlen(str);
	s = (char *)malloc(sizeof(char) * len + 2);
	k = 0;
	while (k < i)
	{
		s[k] = str[k];
		k++;
	}
	s[k] = c;
	while (str[k] != 0)
	{
		s[k + 1] = str[k];
		k++;
	}
	s[k + 1] = '\0';
	free(str);
	return (s);
}

void	ft_strcopy_fr(char **line, char *str)
{
	int k;

	free(*line);
	k = ft_strlen(str);
	*line = (char *)malloc(sizeof(char) * k);
	k = 0;
	while (str[k] != '\0')
	{
		(*line)[k] = str[k];
		k++;
	}
	(*line)[k] = '\0';
}

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

void	ft_key_delete(t_history **hist, char **line, int *pos)
{
	tputs(tgetstr("dc", 0), 1, ft_putchar);
	*line = ft_del_symbol(*line, (*pos) + 1);
	ft_change_struct(hist, *line);
}

void	ft_key_symbol(t_history **hist, char **line, char *str, int *pos)
{
	tputs(tgetstr("im", 0), 1, ft_putchar);
	write(1, str, 1);
	tputs(tgetstr("ei", 0), 1, ft_putchar);
	*line = ft_add_symbol_str(*line, *str, *pos);
	ft_change_struct(hist, *line);
	(*pos)++;
}

void    ft_press_key(t_data *data, char **line, int pos)
{
	char	str[5];
	int		l;

	l = read(0, str, 5);    //! Проверить на ошибку чтения
	while (ft_strncmp(str, "\n", 1) != 0 && l > 0)
	{
		if (!ft_strncmp(str, "\e[A", 3))   //* стрелка вверх
			ft_key_up(&(data->history), line, &pos);
		else if (!ft_strncmp(str, "\e[B", 3))		//* стрелка вниз
			ft_key_down(&(data->history), line, &pos);
		else if (!ft_strncmp(str, "\e[D", 3))		//* стрелка влево
			ft_key_left(&pos);
		else if (!ft_strncmp(str, "\e[C", 3))		//* стрелка вправо
			ft_key_right(*line, &pos);
		else if (!ft_strncmp(str, "\x7f", 1))		//* стрелка backspace
			ft_key_backspace(&(data->history), line, &pos);
		else if (!ft_strncmp(str, "\e[3", 3))		//* стрелка delete
			ft_key_delete(&(data->history), line, &pos);
		else
			ft_key_symbol(&(data->history), line, str, &pos);
		ft_memset(str, 0, 5);
		l = read(0, str, 5);
	}
}

int read_line(t_data *data)
{
    char *line;
    int pos;
        //! необходимо открыть файл для чтения и записи (если его нет, то создать). Всю историю (если она есть )
	//! из файла скопировать в hist.line
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
