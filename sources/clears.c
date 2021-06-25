#include "my_shell.h"

void		free_array(void **s)
{
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != NULL)
			g_free(s[i++]);
		g_free(s);
	}
}

void free_struct(t_data *data)
{
	ft_parsclear(&(data->curr_pars));
	free_array((void **)data->envp);
	g_free(data->line);
	g_free(data->index);
}

void	g_free(void *content)
{
	if (content != NULL)
	{
		free(content);
		content = NULL;
	}
}