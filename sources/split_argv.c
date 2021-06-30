#include "my_shell.h"

static int		get_nstrs(char *str)
{
	int		n_strs;
	int		i;
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

static void		ft_strscpy(char **res, int n, char *str)
{
	int		i[2];
	int		len;

	i[0] = 0;
	i[1] = 0;
	while (str[i[1]] && i[0] < n)
	{
		while (str[i[1]] && str[i[1]] == ' ')
			i[1]++;
		len = chr_in_str(' ', &str[i[1]]);
		if (len == -1)
			len = ft_strlen(&str[i[1]]);
		res[i[0]] = ft_strdupn(&str[i[1]], len);
		if (res[i[0]++] == NULL)
		{
			free_array((void **)res);
			return ;
		}
		i[1] += len + 1;
		while (str[i[1]] && str[i[1]] == ' ')
			i[1]++;
	}
	res[i[0]] = NULL;
}

char			**argv_split(char *s)
{
	char	*str;
	char	**res;
	int		nstrs;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	nstrs = get_nstrs(str);
	res = (char **)malloc(sizeof(char *) * (nstrs + 1));
	if (res == NULL)
		return (NULL);
	ft_strscpy(res, nstrs, str);
	return (res);
}
