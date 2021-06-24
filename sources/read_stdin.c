#include "my_shell.h"

int			ft_stdin_active(char *str, t_data *data)
{
	int		i[2];

	i[0] = -1;
    i[1] = 0;
	while (str[++i[0]] != '\0')
	{
        if (ft_strncmp(&str[i[0]], "<<", 2) == 0 && backslash_is_active(str, i[0]) == 0 
				&& quaote_is_open(str, i[0]) == 0)
			i[1]++;
	}
	i[1] -= tmp_files_size(data->tmp_files);
	return (i[1]);
}

char		*get_end_input(char *str, t_data *data)
{
	char	*end_input;
	int		n_files;
	int		i[2];

	n_files = tmp_files_size(data->tmp_files);
	i[0] = -1;
    i[1] = -1;
	while (str[++i[0]] != '\0' && i[1] < n_files)
	{
        if (ft_strncmp(&str[i[0]], "<<", 2) == 0 && backslash_is_active(str, i[0]) == 0 
				&& quaote_is_open(str, i[0]) == 0)
			i[1]++;
		while (i[1] == n_files && (str[i[0]] == ' ' || str[i[0]] == '<'))
			i[0]++;
	}
	i[1] = i[0] - 1;
	while (str[i[1]] && (str[i[1]] != ' ' || (quaote_is_open(str, i[1]) != 0
			|| backslash_is_active(str, i[1]) != 0)))
		i[1]++;
	end_input = ft_strdupn(&str[i[0] - 1], i[1] - i[0] + 1);
	return (quaote_backslash_clean(end_input));
}

char		*get_filename(t_data *data)
{
	int		n_files;
	char	*nbr;
	char	*fname;

	n_files = tmp_files_size(data->tmp_files) + 1;
	nbr = ft_itoa(n_files);
	nbr = g_strjoin(ft_strdup("."), 0, 0, nbr);
	fname = g_strjoin(nbr, 0, 0, ft_strdup("_tmp_redir.tmp"));
	return (fname);
}

int		read_tmp_stdin(t_data *data, char *str, int *error)
{
	t_tmp_files	*new;
	char	*line;
	char	*end_input;
	char	*fname;
	int		fd;

	end_input = get_end_input(str, data);
	line = NULL;
	fname = get_filename(data);
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd > 0)
	{
		line = rl_gets_without_hist(QUAOTE_PROMT, error);
		while (line && end_input && ft_strcmp(line, end_input) != 0 && *error == 0) // проверить на ^D ^C
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			line = rl_gets_without_hist(QUAOTE_PROMT, error);
		}
		close(fd);
		if (line == NULL)
			write(1, "\e[1A", 1);
		new = tmp_files_new(data->count_files + 1, fname);
		tmp_files_add_back(&(data->tmp_files), new);
		data->count_files += 1;
	}
	else
		g_free(fname);
	g_free(line); // del if (line)
	g_free(end_input);
	return (*error);
}