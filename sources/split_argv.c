#include "my_shell.h"

static size_t	get_nstrs(char *str)
{
	size_t	n_strs;
	int     i;
	int		len;

	n_strs = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			n_strs++;
		len = chr_in_str(' ', &str[i]);
		if (len > -1)
			i += len;
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (n_strs);
}

static void		ft_strscpy(char **res, size_t n, char *str)
{
	size_t	i;
    int     j;
	int		len;

	i = 0;
    j = 0;
	while (str[j] && i < n)
	{
		while (str[j] && str[j] == ' ')
			j++;
        len = chr_in_str(' ', &str[j]);
		if (len == -1)
			len = ft_strlen(&str[j]);
		res[i] = g_strdupn(&str[j], len);
		if (res[i++] == NULL)
		{
			free_array((void **)res);
			return ;
		}
		j += len + 1;
		while (str[j] && str[j] == ' ')
			j++;
	}
	res[i] = NULL;
}

char			**argv_split(char *s)
{
	char	*str;
	char	**res;
	size_t	nstrs;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	nstrs = get_nstrs(str);
	res = (char **)g_malloc(sizeof(char *) * (nstrs + 1));
	if (res == NULL)
		return (NULL);
	ft_strscpy(res, nstrs, str);
	return (res);
}

