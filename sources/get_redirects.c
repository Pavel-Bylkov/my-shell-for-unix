#include "mshell.h"

int	is_redir(char c)
{
	return (c == '>' || c == '<' || c == '&');
}

void	add_redir(t_redir **new, char *str, int *i, t_data *data)
{
	if (!ft_isdigit(str[i[0]]))
		i[0] = i[1];
	i[2] = i[0];
	while (str[i[2]] && ft_isdigit(str[i[2]]))
		i[2]++;
	while (is_redir(str[i[2]]))
		i[2]++;
	i[3] = i[2];
	while (str[i[3]] == ' ')
		i[3]++;
	i[1] = i[3];
	while (str[i[1]] && (str[i[1]] != ' '
			|| (quaote_is_open(str, i[1]) != 0
				|| backslash_is_active(str, i[1]) != 0)))
		i[1]++;
	data->tmp_fcpec = &str[i[0]];
	data->tmp_out = &str[i[3]];
	ft_redir_add(new, ft_redirnew(data, i[2] - i[0], i[1] - i[3]));
}

t_redir	*get_redirects(char *str, t_data *data)
{
	t_redir		*new;
	int			i[4];

	i[0] = -1;
	new = NULL;
	while (str[++i[0]])
	{
		i[1] = i[0];
		while (str[i[1]] && ((!is_redir(str[i[1]]) && str[i[1]] != ' ')
				|| (quaote_is_open(str, i[1]) != 0
					|| backslash_is_active(str, i[1]) != 0)))
			i[1]++;
		if (is_redir(str[i[1]]))
			add_redir(&new, str, i, data);
		i[0] = i[1];
		i[0] -= (str[i[0]] == '\0');
	}
	return (new);
}
