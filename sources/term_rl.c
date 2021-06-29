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

void	eof_symbol(void)
{
	write(1, "d", 1);
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
	else if (ft_isprint(str[0]))
		ft_key_symbol(line, str, pos);
}

void	open_close_fd(int k, int fd)
{
	static int	savefd;

	if (k == 0)
		savefd = fd;
	else
	{
		close(savefd);
	}	
}

void	hand_c(int sig)
{
	if (sig == SIGINT)
		open_close_fd(1, 0);
		//write(0, "\x03\x04\x04\x04\0", 5);
	return ;
}	

void    ft_press_key(char **line, int pos, int *error)
{
	char	str[5];
	int		l;
	int		fd;

	fd = dup(0);
	signal(SIGINT, hand_c);
	signal(SIGQUIT, SIG_IGN);
	open_close_fd(0, fd);
	*line = (char *)malloc(sizeof(char) + 1);
	*line[0] = '\0';
	ft_memset(str, 0, 5);
	l = read(fd, str, 5);    //! Проверить на ошибку чтения
	if (l < 0)
		*error = 1;
	while (ft_strncmp(str, "\n", 1) != 0 && l > 0 && 
		!(pos == 0 && !ft_strncmp(str, "\x04", 1)) && *error == 0)
	{
		choise_keys(str, line, &pos);
		ft_memset(str, 0, 5);
		l = read(fd, str, 5);
		if (l < 0)
			*error = 1;
	}
	if ((pos == 0 && !ft_strncmp(str, "\x04", 1)) || *error == 1)
	{
		g_free(*line);
		*line = NULL;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	//! отработать пустую строку и стрл д в режиме пустой строуи и на 6 символ
}

// void	term_restore(void)
// {
// 	pid_t			pid;

// 	pid = fork();
// 	if (pid == 0)
// 		execve("stty sane", );
// }

char    *term_readline(char *promt, int *error)
{
    struct termios  term;
	char            *term_name;
    char            *line;
	unsigned long 	tmp;
	
	term_name = "xterm-256color";
	tcgetattr(0, &term);
	tmp = term.c_lflag;
	term.c_lflag &= ~(ECHO);
	term.c_lflag &=~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
    ft_putstr_fd(promt, 1);
    tputs(save_cursor, 1, ft_putchar);
    ft_press_key(&line, 0, error);
	tputs(restore_cursor, 1, ft_putchar);
	if (line != NULL)
		write(0, line, ft_strlen(line));
    // write(1, "\n", 1);
	term.c_lflag = tmp;
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);
    return (line);
}
