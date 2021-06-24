#include "my_shell.h"

static int		get_len_command(char *str, char *chars)
{
	int	j;
	int	len[3];
	int min;

	j = 0;
	while (j < 3)
	{
		len[j] = chr_in_str(chars[j], str);
		if (len[j] > -1 && (str[len[j] + 1] == '|' || str[len[j] + 1] == '&'))
			len[j] += 1;
		j++;
	}
	min = -1;
	while (--j > -1)
	{
		if (len[j] > -1 && (min == -1 || len[j] < min))
			min = len[j];
	}
	return ((min == -1) * ft_strlen(str) + (min != -1) * (min + 1));
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
		len = get_len_command(&str[i], "|;&");
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
        len = get_len_command(&str[j], "|;&");
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