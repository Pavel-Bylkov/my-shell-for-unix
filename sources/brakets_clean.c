#include "my_shell.h"

int			brackets_is_open(char *str, int n)
{
	int		i[2];

	i[0] = -1;
    i[1] = 0;
	while (str[++i[0]] != '\0' && i[0] < n)
	{
        if (str[i[0]] == '(' && backslash_is_active(str, i[0]) == 0
				&& quaote_is_open(str, i[0]) == 0)
			++i[1];
        else if (str[i[0]] == ')' && backslash_is_active(str, i[0]) == 0
				&& quaote_is_open(str, i[0]) == 0)
			--i[1];
	}
	return (i[1]);
}

char		*brackets_clean(char *str)
{
	char	*rez;
	int		i;
	int		j;

	rez = (char *)malloc(ft_strlen(str) + 1);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '(' && backslash_is_active(str, i) == 0 &&
				quaote_is_open(str, i) == 0)
			continue ;
		if (str[i] == ')' && backslash_is_active(str, i) == 0 &&
				quaote_is_open(str, i) == 0)
			continue ;
		rez[++j] = str[i];
	}
	rez[++j] = '\0';
	ft_free(&str);
	return (rez);
}
