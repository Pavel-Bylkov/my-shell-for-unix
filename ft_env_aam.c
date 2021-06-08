#include "my_shell.h"

void	ft_env_output(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->size)
	{
		if (!(ft_char_in_str(data->envp[i], '=') == (int)ft_strlen(data->envp[i])))
		{
			write(1, data->envp[i], ft_strlen(data->envp[i]));
			write(1, "\n", 1);
		}
	}
}

void	ft_env_output_err(char *str)
{
	write(1, "my_shell: env: ", 15);
	write(1, "`", 1);
	write(1, str, ft_strlen(str));
	write(1, "': invalid argument\n", 20);
}
