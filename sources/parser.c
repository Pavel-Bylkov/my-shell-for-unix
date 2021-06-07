#include "my_shell.h"

t_pars		*ft_parsnew(int error, char *path, char **argv, char *f_spec)
{
	t_pars	*rez;
	int		j;

	rez = (t_pars *)malloc(sizeof(*rez));
	if (rez == NULL)
		return (NULL);
	if (path)
	{
		j = -1;
		rez->path = (char *)malloc(sizeof(char) * ft_strlen(path) + 1);
		while (path[++j] != '\0')
			rez->path[j] = path[j];
		rez->path[j] = '\0';
	}
	else
		rez->path = NULL;
	rez->argv = argv;
	rez->next = NULL;
	rez->redirect = NULL;
	rez->error = error;
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

// void				ft_parsclear(t_pars **lst, void (*del)(void*));

t_redir		*get_redirects(char *str)
{
	t_redir		*new=NULL;

	(void)str;
	returm (new);
}

int			is_redir(char c)
{
	return (c == '>' || c == '<' || c == '&');
}

void		get_fspec_commands(char *str, char *f_spec)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if (len > 0)
		f_spec[i++] = str[len - 1];
	f_spec[i] = '\0';
}

char		*get_argv(char *str)
{
	int			i[4];
	char		buff[1024];
	char		*argv;
	int			f;

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	argv = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	f = 0;
	while (str[++i[0]])
	{
		if (str[i[0]] == ' ' && f == 0 && quaote_is_open(str, i[0]) == 0
            && backslash_is_active(str, i[0]) == 0 && i[1] > -1)
		{
			i[3] = 0;
			while (buff[i[3]] && i[3] <= i[1])
				argv[++i[2]] = buff[i[3]++];
			argv[++i[2]] = ' ';
		}
		else if (!is_redir(str[i[0]]) || quaote_is_open(str, i[0]) != 0
            || backslash_is_active(str, i[0]) != 0)
			buff[++i[1]] = str[i[0]];
		else
			f = 1; // доделать завтра
	}
	argv[++i[2]] = '\0';
	return (argv);
}

t_pars		*pars_command(char *str)
{
	t_pars		*new;
	char 		f_spec[10];
	char		*argv;

	argv = get_argv(str);
	get_fspec_commands(str, &f_spec); 
	new = ft_parsnew(0, NULL, argv_split(argv), f_spec);
	new->redirect = get_redirects(str); // если нашли редиректы добавляем в список
	free(argv);
	return (new);
}

int parse_line(t_data *data, int error)
{
	int i;
	char **commands;

	if (error != 0)
		return (error);
	commands = get_commands(data); // последний символ | или ;
	if (commands != NULL)
	{
		i = -1;
		while (commands[++i] != NULL)
		{
			ft_parsadd_back(&(data->curr_pars), pars_command(commands[i]));
			// подставить переменные из env
			// заменить на имена файлов, а абс пути для не builtin комманд перенести в path
			// убрать кавычки вокруг цитат
			// проверить наличие файлов, добавить ошибки
		}
		free_array((void **)commands);
		return (0);
	}
	return (2);
}
