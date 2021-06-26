#include "my_shell.h"

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