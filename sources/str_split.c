#include "my_shell.h"

int         backslash_is_active(char *str, int n)
{
    int		i[2];

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

int			quaote_is_open(char *str, int n)
{
	int		i[2];
	int		f[3]; // 0 - open' 1 - open" 2 - activ '\'

	i[0] = -1;
    i[1] = 0;
	ft_memset(f, 0, sizeof(f));
	while (str[++i[0]] != '\0' && i[0] < n)
	{
        if (str[i[0]] == '\\' && f[0] == 0)
			++i[1];
        else if (str[i[0]] == '\'' ||  str[i[0]] == '"')
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

int	    chr_in_str(char c, char *s)
{
	int 	i;

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

// static char		*ft_strdupn(char *s, size_t	n)
// {
// 	char	*res;
//     size_t	i;

// 	res = (char *)malloc(n + 1);
// 	if (res == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i != n && s[i])
// 	{
// 		res[i] = s[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

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
			i += len + 1;
		else
			i += ft_strlen(&str[i]);
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

static int		get_len_command(char *str)
{
	int		len[5];

	len[0] = chr_in_str('|', str);
	len[0] += (len[0] > -1) * (str[len[0] + 1] == '|');
	len[1] = chr_in_str(';', str);
	len[2] = chr_in_str('&', str);
	len[3] = 0;
	while (len[2] > -1)
	{
		len[3] += len[2];
		if (str[len[3] + 1] == '&')
		{
			len[3] += 1;
			break ;
		}
		len[2] = chr_in_str('&', &str[len[3]]);
	}
	// определить кто из них победил ))
	if (len[0] > -1 && len[1] > -1 && len[0] < len[1])
		return (len[0] + 1);
	else if (len[0] > -1 && len[1] > -1 && len[0] > len[1])
		return (len[1] + 1);
	else if (len[0] > -1)
		return (len[0] + 1);
	else if (len[1] > -1)
		return (len[1] + 1);
	else
		return (ft_strlen(str));
}

static int	get_ncommand(t_data *data)
{
	int		n_strs;
	int     i;
	int		len;
	char	*str;

	n_strs = 0;
	i = 0;
	str = data->line;
	while (str[i])
	{
		if (str[i])
			n_strs++;
		// проверить на пустые команды - выйти с ошибкой без парсинга
		len = get_len_command(&str[i]);
		if (len == 0 && str[i] == '|')
			return (print_err(152, data));
		else if (len == 0 && str[i] == ';')
			return (print_err(153, data));
		i += len;
	}
	return (n_strs);
}

static int		commandscpy(char **res, size_t n, char *str)
{
	size_t	i;
    int     j;
	int		len;

	i = 0;
    j = 0;
	while (str[j] && i < n)
	{
        len = get_len_command(&str[j]);
		res[i] = g_strdupn(&str[j], len);
		if (res[i++] == NULL)
		{
			free_array((void **)res);
			return (0);
		}
		j += len;
	}
	res[i] = NULL;
	return (1);
}

char	**get_commands(t_data *data)
{
	char	**commands;
	int		nstrs;

	// сделать по аналогии разложение на команды, с оставлением окончания.
	if (data->line == NULL)
		return (NULL);
	nstrs = get_ncommand(data);
	commands = NULL;
	if (nstrs != -1)
	{
		commands = (char **)g_malloc(sizeof(char *) * (nstrs + 1));
		if (commands == NULL)
			return (NULL);
		if (commandscpy(commands, nstrs, data->line))
			return (commands);
	}	
	if (commands != NULL)
		free_array((void **)commands);
	return (NULL);
}
