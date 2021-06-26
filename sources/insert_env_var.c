#include "my_shell.h"

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
	g_free(str);
	return (rez);
}

int		is_var_chars(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
			(c >= '0' && c <= '9') || c == '_');
}

char	*get_var(char **envp, char *buff, char *str, int *i)
{
	char 	*value;
	int		j;
	char	varname[1024];


	value = NULL;
	if (str[i[1]] == '{')
		while (str[++i[1]] && str[i[1]] != '}')
			varname[++i[2]] = str[i[1]];
	if (is_var_chars(str[i[1] + 1]))
		while (str[++i[1]] && is_var_chars(str[i[1]]))
            varname[++i[2]] = str[i[1]];
	varname[++i[2]] = '\0';
	if (envp)
	{
		j = -1;
		while (envp[++j] != NULL)
			if (ft_strncmp(envp[j], varname, ft_strlen(varname)) == 0)
				value = ft_strdup(&envp[j][ft_strlen(varname) + 1]);
	}
	return (g_strjoin(buff, 0, 0, backslash_add(value)));
}

char    *get_varname(char *str, int *i, t_data *data, char *buff)
{
	if (ft_strncmp(&str[i[1]], "$?", 2) == 0 || 
		ft_strncmp(&str[i[1]], "${?}", 4) == 0)
    {
        buff = g_strjoin(buff, 0, 0, ft_itoa(data->code_exit));
        i[1] += ((ft_strncmp(&str[i[1]], "$?", 2) == 0) + 
                (ft_strncmp(&str[i[1]], "${?}", 4) == 0) * 3);
    }
    else if (str[i[1]] == '$' && str[i[1] + 1] == '{')
    {
        i[1]++;
        buff = get_var(data->envp, buff, str, i);
    }
    else if (str[i[1]] == '$' && ft_isdigit(str[i[1] + 1]))
        i[1]++;
    else if (str[i[1]] == '$' && is_var_chars(str[i[1] + 1]))
    {
        buff = get_var(data->envp, buff, str, i);
        i[1]--;
    }
    else if (str[i[1]] == '$' && (ft_strncmp(&str[i[1]], "$ ", 2) == 0
        ||	ft_strncmp(&str[i[1]], "$\"", 2) == 0 || 
			ft_strncmp(&str[i[1]], "$'", 2) == 0))
        buff = g_strjoin(buff, 0, 0, ft_strdupn(&str[i[1]++], 2));
    return (buff);
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
		while (str[i[1]] && (str[i[1]] != '$' || backslash_is_active(str, i[1]) != 0
			||  quaote_is_open(str, i[1]) == 1))
			i[1]++;
		if (str[i[1]] == '\0')
			buff = g_strjoin(buff, 0, 0, ft_strdup(&str[i[0]]));
		else
			buff = g_strjoin(buff, 0, 0, ft_strdupn(&str[i[0]], i[1] - i[0]));
		i[2] = -1;
		buff = get_varname(str, i, data, buff);
		i[0] = i[1] - (str[i[1]] == '\0');
	}
	g_free(str);
	return (buff);
}
