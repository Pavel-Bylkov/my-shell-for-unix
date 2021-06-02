#include "my_shell.h"

static void	ft_print_error(int fd, int errcode, t_data *data, int i)
{
	char	*line;

	i = 1;
	line = NULL;
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		if (line != NULL && !ft_strncmp(line, "code #", 6))
		{
			if (ft_atoi(&line[6]) == errcode)
			{
				ft_putendl_fd("Error", 2);
				while (i > 0 && line != NULL && ft_strncmp(line, "##", 2))
				{
					ft_putendl_fd(line, 2);
					free(line);
					i = get_next_line(fd, &line);
				}
				if (conf != NULL && conf->err_str != NULL)
					ft_putendl_fd(conf->err_str, 2);
			}
		}
		if (line != NULL)
			free(line);
	}
}

void		print_err(int errcode, t_conf *conf)
{
	int	fd;

	if (errcode < 150)
		ft_putendl_fd(strerror(errno), 2);
	else
	{
		fd = open(ERRORS_FILE, O_RDONLY);
		if (fd > 0)
		{
			ft_print_error(fd, errcode, conf, 1);
			if (close(fd) != 0)
				ft_putendl_fd("Error\nCannot close file with errors.", 2);
		}
		else
			ft_putendl_fd("Error\nCannot open file with errors.", 2);
	}
}
