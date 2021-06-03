#include "my_shell.h"

void		print_err(int errcode, t_data *data)
{
	t_error *tmp;

	tmp = data->errors;
	while (tmp != NULL)
	{
		if (tmp->code == errcode)
		{
			ft_putendl_fd(tmp->text, 2);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_add_error(t_error **list, char *str)
{
	int			j;
	t_error	*temp;

	temp = (t_error *)malloc(sizeof(t_error));
	j = 0;
	while (str[j] && (ft_isdigit(str[j]) || str[j] == ' ' || str[j] == ':'))
		j++;
	temp->text = (char *)malloc(sizeof(char) * (ft_strlen(str) - j));
	while (str[j] != '\0')
	{
		temp->text[j] = str[j];
		j++;
	}
	temp->text[j] = '\0';
	temp->code = ft_atoi(str);
	temp->next = (*list);
	(*list) = temp;
}

t_error 	*errors_create(void)
{
	t_error	*errors;
	char	*line;
	int		fd;
	int		i;

	errors = NULL;
	fd = open(ERRORS_FILE, O_RDONLY);
	if (fd > 0)
	{
		i = 1;
		line = NULL;
		while (i > 0)
		{
			i = get_next_line(fd, &line);
			if (line != NULL)
			{		
				ft_add_error(&errors, line);
				free(line);
				line = NULL;
			}
		}
		if (close(fd) != 0)
			ft_putendl_fd("Error\nCannot close file with errors.", 2);
	}
	else
		ft_putendl_fd("Error\nCannot open file with errors.", 2);
	return (errors);
}

void		ft_exit_errcode(int errcode, t_data *data)
{
	print_err(errcode, data);
	free_struct(data);
	exit(EXIT_FAILURE);
}