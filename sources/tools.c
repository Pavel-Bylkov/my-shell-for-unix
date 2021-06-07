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
	(void)data;
}

int run_comands(t_data *data, int error)  //! Функция aamarei (моя)
{
	if (error != 0)
		return (error);
    //aam_main(data);
    return (0);
}

int free_tmp_data(t_data *data)
{
    print_pars(data);
    return (0);
}

void free_struct(t_data *data)
{
    data->curr_pars = NULL;
	free_array((void **)data->envp);
	ft_historyclear(&(data->history));
	ft_errorsclear(&(data->errors));
	free_array((void **)data->index);
}
