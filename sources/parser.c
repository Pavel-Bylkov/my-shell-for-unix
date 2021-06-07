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

t_pars		*pars_command(char *str)
{
	t_pars		*new=NULL;
	int			i;

	i = -1;
	while (str[++i])
	{
		(void)i;
	}
	new->redirect = get_redirects(str);
	return (new);
}

int parse_line(t_data *data, int error)
{
	int i;
	char **commands;

	if (error != 0)
		return (error);
	commands = get_commands(data->history->line); // последний символ | или ;
	i = -1;
	while (commands[++i] != NULL) // идем до конца строки
		// если нашли редиректы - создаем список
		ft_parsadd_back(&(data->curr_pars), pars_command(commands[i]));
	free(commands);
    return (0);
}
