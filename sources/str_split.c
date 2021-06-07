#include "my_shell.h"

int	    chr_in_str(char c, const char *s)
{
	int 	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char		*ft_strdupchr(char *s, char c)
{
	char	*res;
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	res = (char *)malloc(i + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
//if (s1[i] && (chr_in_str(s1[i], "lhLzjtIq") > -1))
static size_t	get_nstrs(char *str)
{
	size_t	n_strs;

	n_strs = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if (*str)
			n_strs++;
		while (*str && *str != ' ')
			str++;
	}
	return (n_strs);
}

static void		ft_strscpy(char **res, size_t n, char *str)
{
	size_t	i;

	i = 0;
	while (*str && i < n)
	{
		while (*str && *str == ' ')
			str++;
		res[i] = ft_strdupchr(str, ' ');
		if (res[i++] == NULL)
		{
			free_array((void **)res);
			return ;
		}
		while (*str != ' ' && *str)
			str++;
	}
	res[i] = NULL;
}

char			**str_split(char *s)
{
	char	*str;
	char	**res;
	size_t	nstrs;

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