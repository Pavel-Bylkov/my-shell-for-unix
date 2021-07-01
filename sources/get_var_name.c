#include "mshell.h"

int	is_var_chars(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_');
}

char	*get_var(char **envp, char *buff, char *str, int *i)
{
	char	*value;
	int		j;
	char	varname[1024];

	value = NULL;
	while (str[++i[1]] && is_var_chars(str[i[1]]))
		varname[++i[2]] = str[i[1]];
	varname[++i[2]] = '=';
	varname[++i[2]] = '\0';
	if (envp)
	{
		j = -1;
		while (envp[++j] != NULL)
			if (ft_strncmp(envp[j], varname, ft_strlen(varname)) == 0)
				value = ft_strdup(&envp[j][ft_strlen(varname)]);
	}
	value = backslash_add(value);
	if (value == NULL)
		value = ft_strdup("");
	return (ft_g_strjoin(buff, 0, 0, value));
}

int	is_novar_cahars(char *str, int *i)
{
	return (str[i[1]] == '$' && (ft_strncmp(&str[i[1]], "$ ", 2) == 0
			|| str[i[1] + 1] == '\0' || (ft_strncmp(&str[i[1]], "$\"", 2) == 0
				&& quaote_is_open(str, i[1]) == 2) || str[i[1] + 1] == '\\'));
}

char	*add_code_exit(char *str, int *i, t_data *data, char *buff)
{
	char	*res;

	res = ft_g_strjoin(buff, 0, 0, ft_itoa(data->code_exit));
	i[1] += ((ft_strncmp(&str[i[1]], "$?", 2) == 0)
			+ (ft_strncmp(&str[i[1]], "${?}", 4) == 0) * 3);
	return (res);
}

char	*get_varname(char *str, int *i, t_data *data, char *buff)
{
	if (ft_strncmp(&str[i[1]], "$?", 2) == 0
		|| ft_strncmp(&str[i[1]], "${?}", 4) == 0)
		buff = add_code_exit(str, i, data, buff);
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
	else if (is_novar_cahars(str, i))
		buff = ft_g_strjoin(buff, 0, 0, ft_strdupn(&str[i[1]++], 2));
	else if (str[i[1]] == '$' && (ft_strncmp(&str[i[1]], "$\"", 2) == 0
			|| ft_strncmp(&str[i[1]], "$'", 2) == 0))
		buff = ft_g_strjoin(buff, 0, 0, ft_strdupn(&str[++i[1]], 1));
	return (buff);
}
