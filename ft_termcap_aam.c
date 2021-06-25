#include <term.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "includes/my_shell.h"
#include "gnl/get_next_line.h"

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	ft_new_list(t_history **list, char *str, int len)
{
	int		j;

	*list = (t_history *)malloc(sizeof(t_history));
	j = 0;
	(*list)->line = (char *)malloc(sizeof(char) * len);
	while (str[j] != '\0')
	{
		(*list)->line[j] = str[j];
		j++;
	}
	(*list)->line[j] = '\0';
	(*list)->next = NULL;
	(*list)->prev = NULL;
}

void	ft_add_list(t_history **list, char *str, int len)
{
	t_history	*temp;
	int			j;

	temp = (t_history *)malloc(sizeof(t_history));
	j = 0;
	temp->line = (char *)malloc(sizeof(char) * len + 1);
	while (str[j] != '\0')
	{
		temp->line[j] =  str[j];
		j++;
	}
	temp->line[j] = '\0';
	temp->prev = NULL;
	temp->next = (*list);
	(*list)->prev = temp;
	(*list) = temp;
}

t_history	*ft_hist_create(t_history *hist, int fd_hist)
{
	int			res;
	int			len;
	char		*line;

	res = get_next_line(fd_hist, &line);
	while (res == 1)
	{
		len = ft_strlen(line);
		if (hist == NULL)
			ft_new_list(&hist, line, len);
		else
			ft_add_list(&hist, line, len);

		free(line);
		res = get_next_line(fd_hist, &line);
	}
	if (res != 0)
	{
		if (hist == NULL)
			ft_new_list(&hist, line, len);
		else
			ft_add_list(&hist, line, len);
	}
	free(line);
	return (hist);
}

void	ft_change_struct(t_history **list, char *str)
{
	int		k;

	k = ft_strlen(str);
	free ((*list)->line);
	(*list)->line = (char *)malloc(sizeof(char) * k + 2);
	k = 0;
	while (str[k] != '\0')
	{
		(*list)->line[k] = str[k];
		k++;
	}
	(*list)->line[k] = '\0';
}

void	ft_last_in_struct(t_history **list, char *str)
{
	int		k;

	k = ft_strlen(str);
	while ((*list)->prev != NULL)
		*list = (*list)->prev;
	free ((*list)->line);
	(*list)->line = (char *)malloc(sizeof(char) * k + 2);
	k = 0;
	while (str[k] != '\0')
	{
		(*list)->line[k] = str[k];
		k++;
	}
	(*list)->line[k] = '\0';
}

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

	if (*line)
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
	if (*pos < ft_strlen(line))
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
void	ft_press_key(t_history *hist, int fd_hist, char *line)
{
	char	str[5];
	int		pos;
	int		l;

	pos = 0;
	tputs(save_cursor, 1, ft_putchar);
	l = read(0, str, 5);    //! Проверить на ошибку чтения
	while (ft_strncmp(str, "\n", 1) != 0)
	{
		if (!ft_strncmp(str, "\e[A", 3))   //* стрелка вверх
			ft_key_up(&hist, &line, &pos);
		else if (!ft_strncmp(str, "\e[B", 3))		//* стрелка вниз
			ft_key_down(&hist, &line, &pos);
		else if (!ft_strncmp(str, "\e[D", 3))		//* стрелка влево
			ft_key_left(&pos);
		else if (!ft_strncmp(str, "\e[C", 3))		//* стрелка вправо
			ft_key_right(line, &pos);
		else if (!ft_strncmp(str, "\x7f", 1))		//* стрелка backspace
			ft_key_backspace(&hist, &line, &pos);
		else if (!ft_strncmp(str, "\e[3", 3))		//* стрелка delete
			ft_key_delete(&hist, &line, &pos);
		else
			ft_key_symbol(&hist, &line, str, &pos);
		ft_memset(str, 0, 5);
		l = read(0, str, 5);
	}
	ft_last_in_struct(&hist, line);
	ft_strcopy_fr(&line, hist->line);
	tputs(restore_cursor, 1, ft_putchar);
	pos = ft_strlen(hist->line);
	write(0, hist->line, pos);

	write(1, "\n", 1);
	if (hist->line[0] != '\0') //если последняя команда не пустая - записываем в файл истории
	{
		write(fd_hist, hist->line, ft_strlen(hist->line));
		write(fd_hist, "\n", 1);
	}
}

int main(int argc, char const *argv[], char const *env[])
{
	char	*line;
	struct termios term;
	char	*term_name;
	t_history	*hist;
	int			fd_hist;

	//! необходимо открыть файл для чтения и записи (если его нет, то создать). Всю историю (если она есть )
	//! из файла скопировать в hist.line

	line = (char *)malloc(sizeof(char) + 1);
	line[0] = '\0';

	fd_hist = open("histoty_command.txt", O_CREAT | O_RDWR, 0666);  //! Надо будет закрыть файл при выходе из минишела
	hist = NULL;
	hist = ft_hist_create(hist, fd_hist);
	ft_add_list(&hist, "", 0);
	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &=~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);

	write(0, "mshl > ", 7);
	ft_press_key(hist, fd_hist, line);
	return (0);
}
