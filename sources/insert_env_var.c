#include "mshell.h"

char	*backslash_add(char *str)
{
	char	*rez;
	int		i;
	int		j;

	if (str == NULL)
		return (NULL);
	rez = (char *)malloc(ft_strlen(str) * 2 + 1);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '\\' || str[i] == '\'' || str[i] == '"')
			rez[++j] = '\\';
		rez[++j] = str[i];
	}
	rez[++j] = '\0';
	ft_free((void **)&str);
	return (rez);
}

char	*insert_var_from_env(t_data *data, char *str)
{
	char	*buff;
	int		i[4];

	i[0] = -1;
	buff = ft_strdup("");
	while (str[++i[0]])
	{
		i[1] = i[0];
		while (str[i[1]] && (str[i[1]] != '$'
				|| backslash_is_active(str, i[1]) != 0
				|| quaote_is_open(str, i[1]) == 1))
			i[1]++;
		if (str[i[1]] == '\0')
			buff = ft_g_strjoin(buff, 0, 0, ft_strdup(&str[i[0]]));
		else
			buff = ft_g_strjoin(buff, 0, 0,
					ft_strdupn(&str[i[0]], i[1] - i[0]));
		i[2] = -1;
		buff = get_varname(str, i, data, buff);
		i[0] = i[1] - (str[i[1]] == '\0');
	}
	ft_free((void **)&str);
	return (buff);
}
