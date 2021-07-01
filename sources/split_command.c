#include "mshell.h"

static int	get_len_command(char *str, char *chars)
{
	int	j;
	int	len[3];
	int	min;

	j = 0;
	while (j < (int)ft_strlen(chars))
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

static int	get_ncommand(char *line, char *s)
{
	int		n_strs;
	int		i;
	int		len;
	char	*str;

	n_strs = 0;
	i = 0;
	str = line;
	while (str[i])
	{
		if (str[i])
			n_strs++;
		len = get_len_command(&str[i], s);
		i += len;
	}
	return (n_strs);
}

static int	commandscpy(char **res, int n, char *str, char *s)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (str[j] && i < n)
	{
		len = get_len_command(&str[j], s);
		res[i] = ft_strdupn(&str[j], len);
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

char	**get_commands(char *line, char *str)
{
	char	**commands;
	int		nstrs;

	if (line == NULL)
		return (NULL);
	nstrs = get_ncommand(line, str);
	commands = NULL;
	if (nstrs != -1)
	{
		commands = (char **)malloc(sizeof(char *) * (nstrs + 1));
		if (commands == NULL)
			return (NULL);
		if (commandscpy(commands, nstrs, line, str))
			return (commands);
	}
	if (commands != NULL)
		free_array((void **)commands);
	return (NULL);
}
