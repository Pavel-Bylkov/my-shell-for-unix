#include "my_shell.h"

t_pars		*ft_parsnew(int error, char *path, char **argv, char *f_spec)
{
	t_pars	*rez;
	int		j;

	rez = (t_pars *)g_malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	if (path)
		rez->path = g_strdup(path);
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

	rez = (t_redir *)g_malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	if (ft_strncmp(f_spec, "<<", 2) != 0)
	{
		j = -1;
		while (++j != l1)
			rez->f_spec[j] = f_spec[j];
		rez->f_spec[j] = '\0';
		rez->out = g_strdupn(out, l2);
	}
	else
	{
		rez->f_spec[0] = '<';
		rez->f_spec[1] = '\0';
		rez->out = g_strdup(
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

	argv = (char *)g_malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_memset(argv, 0, sizeof(argv));
    get_fspec_commands(&str, f_spec);
	get_argv(str, &argv);
	new = ft_parsnew(0, NULL, argv_split(argv), f_spec);
	g_free(argv);
	new->redirect = get_redirects(str);
	return (new);
}

void	get_var(char *str, char *var)
{
	// в первую очередь отработать $?
	(void)str;
	(void)var;
}

void	insert_var_from_env(t_data *data, t_pars *tmp)
{
	char	var[1024];
	int		i;
	int     j;
	int     k;
	char    *value;

	i = -1;
	while (tmp->argv[++i])
	{
	    k = 0;
        while (tmp->argv[i][k] && (tmp->argv[i][k] != '$' || 
			(quaote_is_open(tmp->argv[i], k) == 1
            || backslash_is_active(tmp->argv[i], k) != 0)))
            k++;
        get_var(&tmp->argv[i][k], var);
		value = NULL;
		if (data->envp)
		{
			j = -1;
			while (data->envp[++j] != NULL)
				if (ft_strncmp(data->envp[j], var, ft_strlen(var)) == 0)
					value = data->envp[j];
		}
		(void)value;
	}
}

int		is_builtin(char *str)
{
	return (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 3) == 0 ||
		ft_strncmp(str, "env", 4) == 0 || ft_strncmp(str, "pwd", 4) == 0 ||
		ft_strncmp(str, "export", 7) == 0 || ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "exit", 5) == 0);
}

char	*search_in_path(t_data *data, char *name)
{
	char	*path;
	int		i;
	int		j;
	int		fd;
	char	*abs_path;
	int		flag;

	path = NULL;
	if (data->envp)
	{
		i = -1;
		while (data->envp[++i] != NULL)
			if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
				path = data->envp[i];
	}
	if (path)
	{
		i = 5;
		flag = 0;
		while (path[i] && flag == 0)
		{
			j = i;
			while (path[j] != '\0' && path[j] != ':')
				j++;
			abs_path = g_newpath(&path[i], j - i, name);
			fd = open(abs_path, O_RDONLY);
			if (fd > 0)
			{
				flag = 1;
				close(fd);
			}
			else
				g_free(abs_path);
			i = j + (path[j] == ':') * 1;
		}
		if (flag)
		{
			g_free(name);
			return (abs_path);
		}
	}
	return (name);
}

// заменить на имена файлов, а абс пути для не builtin комманд перенести в path
void	find_path(t_data *data, t_pars *tmp)
{
	int		len;
	char	*name;

	name = tmp->argv[0];
	if (!name)
		return ;
	if (!is_builtin(name) && chr_in_str('/', name) == -1)
		tmp->argv[0] = search_in_path(data, name);
	if (chr_in_str('/', tmp->argv[0]) > -1)
	{
		tmp->path = tmp->argv[0];
		len = ft_strlen(tmp->path);
		while (tmp->path[len - 1] != '/')
			len--;
		tmp->argv[0] = g_strdup(&(tmp->path[len]));
	}
}

char	*quaote_backslash_clean(char *str)
{
	return (str); // временно
}
// убрать кавычки вокруг цитат
void	quaotes_clean(t_pars *tmp)
{
	int		i[2];
	int		f[3];
	char	b[1024];

	i[0] = -1;
	while (tmp->argv[++i[0]])
	{
		i[1] = -1;
		ft_memset(f, 0, sizeof(f));
		while (tmp->argv[i[0]][++i[1]] != '\0')
		{
			b[i[1]] = tmp->argv[i[0]][i[1]];
		}
	}
	(void)b;
}
// проверить наличие файлов, добавить ошибки
void	check_open_files(t_pars *tmp)
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
}

int 	parse_line(t_data *data, int error)
{
	int i;
	char **commands;
	t_pars *new;

	if (error != 0)
		return (error);
	commands = get_commands(data); // последний символ | или ; , || или &&
	if (commands != NULL)
	{
		i = 0;
		while (commands[i] != NULL)
			i++;
		while (--i > -1)
		{
			printf("%s\n", commands[i]);
			new = pars_command(commands[i]);
			ft_parsadd_front(&(data->curr_pars), new);
			//insert_var_from_env(data, new);
			// убрать кавычки вокруг цитат
			//quaotes_clean(new);
			// заменить на имена файлов, а абс пути для не builtin комманд перенести в path
			find_path(data, new);
			// проверить наличие файлов, добавить ошибки
			check_open_files(new);
		}
		free_array((void **)commands);
		return (0);
	}
	return (2);
}
