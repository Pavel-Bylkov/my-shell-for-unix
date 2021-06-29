#include "my_shell.h"

char	*quaote_backslash_clean(char *str)
{
	char	*rez;
	int		i;
	int		j;

	rez = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
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
	ft_free(&str);
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

void	check_open_redir(t_pars *new)
{
	int		fd;
	t_redir	*tmp;

	tmp = new->redirect;
	while (tmp != NULL)
	{
		fd = 0;
		if (ft_strcmp(tmp->f_spec, ">")  == 0)
			fd = open(tmp->out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (ft_strcmp(tmp->f_spec, ">>")  == 0)
			fd = open(tmp->out, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd > 0)
			close(fd);
		tmp = tmp->next;
	}
}

int		check_and_clean_pars(t_data *data, t_pars *new)
{
	int		fd;

	quaotes_clean(new);
	find_path(data, new);
	if (new->path && new->error == 0)
	{
		fd = open(new->path, O_RDONLY);
		if (fd > 0)
			close(fd);
		else
			new->error = errno;
	}
	if (new->redirect)
		check_open_redir(new);
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
			new = pars_command(commands[i], data);
			ft_parsadd_front(&(data->curr_pars), new);
			error = check_and_clean_pars(data, new);
		}
		free_array((void **)commands);
		return (error);
	}
	return (258);
}
