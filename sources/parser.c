#include "my_shell.h"

char	*quaote_backslash_clean(char *str)
{
	char	*rez;
	int		i;
	int		j;

	rez = (char *)malloc(ft_strlen(str) + 1);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '\\' && backslash_is_active(str, i) == 0 &&
				quaote_is_open(str, i) == 0)
			continue ;
		if (str[i] == '\'' && backslash_is_active(str, i) == 0 &&
				(quaote_is_open(str, i) == 1 || quaote_is_open(str, i) != 2))
			continue ;
		if (str[i] == '"' && backslash_is_active(str, i) == 0 &&
				(quaote_is_open(str, i) == 2 || quaote_is_open(str, i) != 1))
			continue ;
		rez[++j] = str[i];
	}
	rez[++j] = '\0';
	g_free(str);
	return (rez);
}

void	quaotes_clean(t_pars *tmp)
{
	int			i;
	t_redir		*redir;

	i = -1;
	while (tmp->argv[++i])
		tmp->argv[i] = quaote_backslash_clean(tmp->argv[i]);
	if (tmp->redirect)
	{
		redir = tmp->redirect;
		while (redir)
		{
			redir->out = quaote_backslash_clean(redir->out);
			redir = redir->next;
		}
	}
}
// проверить наличие файлов, добавить ошибки
int	check_open_files(t_pars *tmp)
{
	int		fd;

	if (tmp->path && tmp->error == 0)
	{
		fd = open(tmp->path, O_RDONLY);
		if (fd > 0)
			close(fd);
		else
			tmp->error = errno;
	}
	return (0);
}

int 	parse_line(char *line, t_data *data, int error)
{
	int i;
	char **commands;
	t_pars *new;

	if (error != 0)
		return (error);
	commands = get_commands(line, "|&");
	if (commands != NULL)
	{
		i = 0;
		while (commands[i] != NULL)
			i++;
		while (--i > -1)
		{
			commands[i] = insert_var_from_env(data, commands[i]);
			new = pars_command(commands[i]);
			ft_parsadd_front(&(data->curr_pars), new);
			quaotes_clean(new);
			find_path(data, new);
			error = check_open_files(new);
		}
		free_array((void **)commands);
		return (error);
	}
	return (258);
}
