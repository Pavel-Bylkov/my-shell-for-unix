#include "my_shell.h"

int	ft_perr(char *com, int code, char *str1, char *str2)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	if (com)
	{
		ft_putstr_fd(com, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str1)
		ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	return (code);
}

int		unexpected_eof(char *str)
{
	char 	*str_err;
	int		len;

	str_err = g_strdup("unexpected EOF while looking for matching `");
	len = ft_strlen(str); // возможно нужно сделать -1
	if (quaote_is_open(str, len) == 1)
		str_err = g_strjoin(str_err, 0, 0, g_strdup("''"));
	else if (quaote_is_open(str, len) == 2)
		str_err = g_strjoin(str_err, 0, 0, g_strdup("\"'"));
	else if (brackets_is_open(str, len) > 0)
		str_err = g_strjoin(str_err, 0, 0, g_strdup(")'"));
	ft_perr(NULL, 2, NULL, str_err);
	g_free(str_err);
	g_free(str);
	return (2);
}

int		unexpected_eof_infile(char *str)
{
	char	*strerr;

	strerr = ft_strjoin(
			"here-document at line 1 delimited by end-of-file (wanted `",
			str);
	strerr = g_strjoin(strerr, 0, 0, g_strdup("')"));
	ft_perr("warning", 0, NULL, strerr);
	free(strerr);
	return (0);
}

int		unexpected_token(char *str, int flag)
{
	char	*strerr;

	strerr = ft_strjoin(
			"syntax error near unexpected token `", str);
	strerr = g_strjoin(strerr, 0, 0, g_strdup("'"));
	ft_perr(NULL, 2, NULL, strerr);
	free(strerr);
	if (flag)
		g_free(str);
	return (2);
}

int		print_err(int errcode, t_data *data)
{
	t_error *tmp;

	tmp = data->errors;
	while (tmp != NULL)
	{
		if (tmp->code == errcode)
		{
			ft_putendl_fd(tmp->text, 2);
			return (-1);
		}
		tmp = tmp->next;
	}
	ft_putendl_fd("my_shell: Error code is not define.", 2);
	return (-1);
}

void	ft_add_error(t_error **list, char *str)
{
	int			j;
	t_error	*temp;

	temp = (t_error *)malloc(sizeof(t_error));
	j = 0;
	while (str[j] && (ft_isdigit(str[j]) || str[j] == ' ' || str[j] == ':'))
		j++;
	temp->text = (char *)malloc(sizeof(char) * (ft_strlen(str) - j + 2));
	while (str[j] != '\0')
	{
		temp->text[j] = str[j];
		j++;
	}
	temp->text[j] = '\0';
	temp->code = ft_atoi(str);
	temp->next = (*list);
	(*list) = temp;
}

t_error 	*errors_create(void)
{
	t_error	*errors;
	char	*line;
	int		fd;

	errors = NULL;
	fd = open(ERRORS_FILE, O_RDONLY);
    if (fd < 0)
        ft_putendl_fd("Error\nCannot open file with errors.", 2);
    line = NULL;
	ft_putendl_fd("start  errors.", 1);
    while (get_next_line(fd, &line) > 0)
    {
		if (line != NULL)
		{
			ft_add_error(&errors, line);
			ft_putendl_fd(line, 1);
			g_free(line);
		}
	}
	ft_putendl_fd("lines create", 1);
    if (line != NULL)
    {
		ft_add_error(&errors, line);
		g_free(line);
	}
    if (close(fd) != 0)
		ft_putendl_fd("Error\nCannot close file with errors.", 2);		
	return (errors);
}

void		ft_exit_errcode(int errcode, t_data *data)
{
	print_err(errcode, data);
	free_struct(data);
	exit(EXIT_FAILURE);
}

void				ft_errorsclear(t_error **lst)
{
	t_error	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->text)
			g_free((*lst)->text);
		g_free((*lst));
		*lst = tmp;
	}
}