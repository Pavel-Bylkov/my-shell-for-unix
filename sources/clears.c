#include "my_shell.h"

void		free_array(void **s)
{
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != NULL)
			ft_free(&s[i++]);
		ft_free(&s);
	}
}

void		free_struct(t_data *data)
{
	ft_parsclear(&(data->curr_pars));
	free_array((void **)data->envp);
	ft_free(&data->line);
	ft_free(&data->index);
}

void		ft_free(void **content)
{
	if (*content != NULL)
	{
		free(*content);
		*content = NULL;
	}
}
