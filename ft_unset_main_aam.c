#include "my_shell.h"

int	ft_unset(t_data *data, t_pars pars)
{
	int		i;

	if (pars.argv[1] != NULL)
	{
		i = 1;
		while (pars.argv[i] != NULL)
		{
			if ((ft_char_in_str(pars.argv[i], '=')
					!= (int)ft_strlen(pars.argv[i]))
				|| (pars.argv[i][0] >= 48 && pars.argv[i][0] <= 57))
			{
				ft_unset_output_err(pars.argv[i]);
				return (1);
			}
			else
				data->envp = ft_env_del(data, pars.argv[i], &(data->size));
			i++;
		}
		create_index(&(*data));
		sort_mass(data->envp, &data->index, data->size);
	}
	return (0);
}
