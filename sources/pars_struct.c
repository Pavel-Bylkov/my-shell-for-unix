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