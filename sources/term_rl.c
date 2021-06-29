#include "my_shell.h"

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

void	choise_keys(char *str, char **line, int *pos)
{
	if (!ft_strncmp(str, "\e[D", 3))		//* стрелка влево
		ft_key_left(pos);
	else if (!ft_strncmp(str, "\e[C", 3))		//* стрелка вправо
		ft_key_right(*line, pos);
	else if (!ft_strncmp(str, "\x7f", 1))		//* стрелка backspace
		ft_key_backspace(line, pos);
	else if (!ft_strncmp(str, "\e[3", 3))		//* стрелка delete
		ft_key_delete(line, pos);
	else
		ft_key_symbol(line, str, pos);
}

void    ft_press_key(char **line, int pos)
{
	char	str[5];
	int		l;

	l = read(0, str, 5);    //! Проверить на ошибку чтения
	while (ft_strncmp(str, "\n", 1) != 0 && l > 0)
	{
		choise_keys(str, line, &pos);
		ft_memset(str, 0, 5);
		l = read(0, str, 5);
	}
	//! отработать пустую строку и стрл д в режиме пустой строуи и на 6 символ
}

char    *term_readline(char *promt)
{
    struct termios  term;
	char            *term_name;
    char            *line;

	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &=~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
    ft_putstr_fd(promt, 1);
    line = (char *)malloc(sizeof(char) + 1);
	line[0] = '\0';
    tputs(save_cursor, 1, ft_putchar);
    ft_press_key(&line, 0);
	tputs(restore_cursor, 1, ft_putchar);
	write(0, line, ft_strlen(line));
    write(1, "\n", 1);
    return (line);
}
