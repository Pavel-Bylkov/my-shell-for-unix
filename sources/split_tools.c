#include "mshell.h"

int	backslash_is_active(char *str, int n)
{
	int	i[2];

	i[0] = -1;
	i[1] = 0;
	while (str[++i[0]] != '\0' && i[0] < n)
	{
		if (str[i[0]] == '\\')
			++i[1];
		else
			i[1] = 0;
	}
	return (i[1] > 0 && i[1] % 2 == 1);
}

int	quaote_is_open(char *str, int n)
{
	int		i[2];
	int		f[3];

	i[0] = -1;
	i[1] = 0;
	ft_memset(f, 0, sizeof(f));
	while (str[++i[0]] != '\0' && i[0] < n)
	{
		if (str[i[0]] == '\\' && f[0] == 0)
			++i[1];
		else if (str[i[0]] == '\'' || str[i[0]] == '"')
		{
			f[2] = (i[1] > 0 && i[1] % 2 == 1);
			i[1] = 0;
		}
		else
			i[1] = 0;
		if (str[i[0]] == '\'' && f[2] == 0)
			f[0] = (f[1] == 0 && f[0] == 0);
		else if (str[i[0]] == '"' && f[2] == 0)
			f[1] = (f[0] == 0 && f[1] == 0);
	}
	return (f[0] + f[1] * 2);
}

int	chr_in_str(char c, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && quaote_is_open(s, i) == 0
			&& backslash_is_active(s, i) == 0)
			return (i);
		i++;
	}
	return (-1);
}
