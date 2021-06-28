#include "my_shell.h"

void		free_array(void **s)
{
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != NULL)
		{
			free(s[i]);
			s[i++] = NULL;
		}
		free(s);
		s = NULL;
	}
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	print_pars(t_data *data)
{
	t_pars *tmp;
	t_redir *last;
	int		i;

	tmp = data->curr_pars;
	while (tmp != NULL)
	{
		ft_putendl_fd("------------------------------------", 1);
		ft_putstr_fd("error : ", 1);
		ft_putnbr_fd(tmp->error, 1);
		ft_putendl_fd("", 1);
		ft_putstr_fd("path : ", 1);
		if (tmp->path != NULL)
			ft_putendl_fd(tmp->path, 1);
		else
			ft_putendl_fd("NULL", 1);
		ft_putendl_fd("argv : ", 1);
		i = -1;
		while (tmp->argv[++i] != NULL)
		{
			ft_putstr_fd("   ", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(" : ", 1);
			ft_putendl_fd(tmp->argv[i], 1);
		}
		ft_putstr_fd("f_spec : ", 1);
		ft_putendl_fd(tmp->f_spec, 1);
		ft_putendl_fd("redirects :", 1);
		last = tmp->redirect;
		while (last != NULL)
		{
			ft_putstr_fd("   -f_spec : ", 1);
			ft_putendl_fd(last->f_spec, 1);
			ft_putstr_fd("   -out : ", 1);
			ft_putendl_fd(last->out, 1);
			last = last->next;
		}
		tmp = tmp->next;
	}
}

int run_comands(t_data *data, int error)  //! Функция aamarei (моя)
{
	if (error != 0)
		return (error);
    aam_main(data);
    return (0);
}

void free_struct(t_data *data)
{
	ft_parsclear(&(data->curr_pars));
	free_array((void **)data->envp);
	ft_historyclear(&(data->history));
	ft_errorsclear(&(data->errors));
	free_array((void **)data->index);
}
