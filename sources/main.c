#define  MAIN_FILE
#include "my_shell.h"


int	main(int argc, char **argv, char **envp)
{
	t_data data;
	int     error;

	init_struct(&data, envp);
	error = 0;
    g_data = &data;
	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
		return (one_run(&data, argv[2]));
	else if (argc == 2)
		error = read_from_file(&data, argv[1]);
	else
		main_loop(&data);
	free_struct(&data);
	return (error);
}

int     one_run(t_data *data, char *str)
{
    int error;
	char **lines;
	int	i;

    error = 0;
    data->line = ft_strdup(str);
    if (data->line == NULL)
		return (0);
    if (check_unexpected_token(data->line) != 0)
		return (258);
    if (error == 0)
	{
		i = -1;
		lines = get_commands(data->line, ";");
		while (lines[++i] != NULL)
		{
			error = parse_line(lines[i], data, error);
			data->code_exit = run_comands(data, error);
			ft_parsclear(&(data->curr_pars));
		}
	}
	g_free((void *)data->line);
	g_tmp_files_clear(&(data->tmp_files));
	data->count_files = 0;
	free_struct(data);
	return (data->code_exit);
}

static int		quaote_open_mode2(t_data *data, int fd, int *ret)
{
    int		len;
    char	*tmp;

    len = ft_strlen(data->line);
    if (check_unexpected_token(data->line) != 0)
        return (2);
    while (*ret > 0 && is_endl_ignor(data->line, data))
    {
        tmp = data->line;
        *ret = get_next_line(fd, &(data->line));
        if (backslash_is_active(tmp, len))
        {
            if (NULL == data->line)
            {
                close(fd);
                exit(EXIT_SUCCESS);
            }
            data->line = g_strjoin(tmp, -1, 0, data->line);
        }
        else if (*ret < 0 && NULL == data->line)
            return (ft_perr(NULL, 2, NULL, "No such file or directory"));
        else if (quaote_is_open(tmp, len) != 0)
            data->line = g_strjoin(tmp, 0, 1, data->line);
        else
            data->line = g_strjoin(tmp, 0, 0, data->line);
    }
    return (0);
}

int        read_from_file(t_data *data, char *filename)
{
    int		    ret;
    int         fd;
    int         error;
	char **lines;
	int	i;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (ft_perr(NULL, errno, filename, strerror(errno)));
    ret = 1;
    error = 0;
    while (ret > 0)
    {
        ret = get_next_line(fd, &(data->line));
        if (data->line == NULL)
            return (0);
        else if (data->line[0] == '\0')
        {
            g_free(data->line);
            continue ;
        }
        else
            error = quaote_open_mode2(data, fd, &ret);
		if (error == 0)
		{
			i = -1;
			lines = get_commands(data->line, ";");
			while (lines[++i] != NULL)
			{
				error = parse_line(lines[i], data, error);
				data->code_exit = run_comands(data, error);
				ft_parsclear(&(data->curr_pars));
			}
		}
        g_free(data->line);
    }
    close(fd);
    return (data->code_exit);
}
