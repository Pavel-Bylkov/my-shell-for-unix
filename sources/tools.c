#include "my_shell.h"

void		free_strs(char **s)
{
	size_t	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		s[i++] = NULL;
	}
	free(s);
	s = NULL;
}

static size_t	get_nstrs(char **str)
{
	size_t	n_strs;
    int	i;

	i = -1;
	n_strs = 0;
	while (str[++i] != NULL)
		n_strs++;
	return (n_strs);
}

static void		ft_strscpy(char **res, size_t n, char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL && i < n)
	{
		res[i] = ft_strdup(str[i]);
		if (res[i++] == NULL)
		{
			free_strs(res);
			return ;
		}
	}
	res[i] = NULL;
}

char            **copy_str_array(char **s)
{
	char	**res;
	size_t	nstrs;

	if (s == NULL)
		return (NULL);
	nstrs = get_nstrs(s);
	res = (char **)malloc(sizeof(char *) * (nstrs + 1));
	if (res == NULL)
		return (NULL);
	ft_strscpy(res, nstrs, s);
	return (res);
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}
