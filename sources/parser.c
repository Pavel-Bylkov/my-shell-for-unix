#include "my_shell.h"

t_pars		*ft_parsnew(int error, char *path, char **argv, char *f_spec)
{
	t_pars	*rez;
	int		j;

	rez = (t_pars *)malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	if (path)
		rez->path = ft_strdup(path);
	else
		rez->path = NULL;
	rez->argv = argv;
	rez->next = NULL;
	rez->redirect = NULL;
	rez->error = error;
	rez->count = 0;
	j = -1;
	while (f_spec[++j] != '\0')
		rez->f_spec[j] = f_spec[j];
	rez->f_spec[j] = '\0';
	return (rez);
}

void		ft_parsadd_back(t_pars **lst, t_pars *new)
{
	t_pars	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void		ft_parsadd_front(t_pars **lst, t_pars *new)
{
	t_pars	*last;

	if (*lst == NULL)
	{
		*lst = new;
		new->count = 1;
	}
	else
	{
		last = *lst;
		new->next = last;
		if (ft_strcmp(new->f_spec, "|") == 0)
			new->count = last->count + 1;
		else
			new->count = 1;
		*lst = new;
	}
}

void		ft_redir_add(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_redir		*ft_redirnew(char *f_spec, int l1, char *out, int l2)
{
	t_redir	*rez;
	int		j;

	rez = (t_redir *)malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	if (ft_strncmp(f_spec, "<<", 2) != 0)
	{
		j = -1;
		while (++j != l1)
			rez->f_spec[j] = f_spec[j];
		rez->f_spec[j] = '\0';
		rez->out = ft_strdupn(out, l2);
	}
	else
	{
		rez->f_spec[0] = '<';
		rez->f_spec[1] = '\0';
		rez->out = ft_strdup(
			get_filename_by_index(g_data->tmp_files, g_data->count_files));
		g_data->count_files -= 1;
	}
	rez->next = NULL;
	return (rez);
}

void				ft_redirclear(t_redir **redir)
{
	t_redir	*tmp;

	while (*redir)
	{
		tmp = (*redir)->next;
		if ((*redir)->out)
			g_free((*redir)->out);
		g_free((*redir));
		*redir = tmp;
	}
}

void				ft_parsclear(t_pars **lst)
{
	t_pars	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->path)
			g_free((*lst)->path);
		if ((*lst)->argv)
			free_array((void **)((*lst)->argv));
		if ((*lst)->redirect)
			ft_redirclear(&((*lst)->redirect));
		g_free((*lst));
		*lst = tmp;
	}
}

int			is_redir(char c)
{
	return (c == '>' || c == '<' || c == '&');
}

t_redir		*get_redirects(char *str)
{
	t_redir		*new;
	int			i[4];

	i[0] = -1;
	new = NULL;
	while (str[++i[0]])
	{
		i[1] = i[0];
		while (str[i[1]] && ((!is_redir(str[i[1]]) && str[i[1]] != ' ')
				|| (quaote_is_open(str, i[1]) != 0
            || backslash_is_active(str, i[1]) != 0)))
			i[1]++;
		if (is_redir(str[i[1]]))
		{
			if (!ft_isdigit(str[i[0]]))
				i[0] = i[1];
			i[2] = i[0];
			while (str[i[2]] && ft_isdigit(str[i[2]]))
				i[2]++;
			while (is_redir(str[i[2]]))
				i[2]++;
			i[3] = i[2];
			while (str[i[3]] == ' ')
				i[3]++;
			i[1] = i[3];
			while (str[i[1]] && (str[i[1]] != ' '
				|| (quaote_is_open(str, i[1]) != 0
            || backslash_is_active(str, i[1]) != 0)))
				i[1]++;
			ft_redir_add(&new, ft_redirnew(&str[i[0]], i[2] - i[0],
					&str[i[3]], i[1] - i[3]));
		}
		i[0] = i[1];
        i[0] -= (str[i[0]] == '\0');
	}
	return (new);
}

void		get_fspec_commands(char **str, char *f_spec)
{
	int	len;
	int	i;

	len = ft_strlen(*str);
	i = 0;
	if (len > 0 && chr_in_str((*str)[len - 1], "|;&") > -1)
    {
        f_spec[i++] = (*str)[len - 1];
        (*str)[len - 1] = '\0';
		if (len > 1 && chr_in_str((*str)[len - 2], "|&") > -1)
		{
			f_spec[i++] = (*str)[len - 2];
			(*str)[len - 2] = '\0';
		}
    }
	f_spec[i] = '\0';
}

int			str_is_fd(char *str, int n)
{
	int		i;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] == ' ')
			i++;
		if (ft_isdigit(str[i]))
			i++;
		else
            return (0);
	}
	return (1);
}

void		get_argv(char *str, char **argv)
{
	int			i[4];

	i[0] = -1;
	i[2] = -1;
	while (str[++i[0]])
	{
		i[1] = i[0];
		while (str[i[1]] && ((!is_redir(str[i[1]]) && str[i[1]] != ' ')
				|| (quaote_is_open(str, i[1]) != 0
            || backslash_is_active(str, i[1]) != 0)))
			i[1]++;
		if (!is_redir(str[i[1]]) || !str_is_fd(&str[i[0]], i[1] - i[0]))
		{
			while (str[i[0]] && i[0] < i[1])
				(*argv)[++i[2]] = str[i[0]++];
			(*argv)[++i[2]] = ' ';
		}
		i[0] = i[1];
		if (is_redir(str[i[0]]))
		{
			while (is_redir(str[i[0]]))
				i[0]++;
			while (str[i[0]] == ' ')
				i[0]++;
			while (str[i[0]] && (str[i[0]] != ' '
				|| (quaote_is_open(str, i[0]) != 0
            || backslash_is_active(str, i[0]) != 0)))
				i[0]++;
		}
        i[0] -= (str[i[0]] == '\0');
	}
	(*argv)[++i[2]] = '\0';
}

t_pars		*pars_command(char *str)
{
	t_pars		*new;
	char 		f_spec[10];
	char		*argv;

	argv = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_memset(argv, 0, sizeof(argv));
    get_fspec_commands(&str, f_spec);
	get_argv(str, &argv);
	new = ft_parsnew(0, NULL, argv_split(argv), f_spec);
	g_free(argv);
	new->redirect = get_redirects(str);
	return (new);
}

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
// убрать кавычки вокруг цитат
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

int 	parse_line(t_data *data, int error)
{
	int i;
	char **commands;
	t_pars *new;

	if (error != 0)
		return (error);
	commands = get_commands(data);
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
