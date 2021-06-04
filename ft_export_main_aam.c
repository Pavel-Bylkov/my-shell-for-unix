#include "includes/my_shell.h"

int	ft_export(t_data *data, t_pars pars)
{
	int		i;

	if (pars.argv[1] == NULL)
		ft_out_export(*data);
	else
	{
		i = 1;
		while (pars.argv[i] != NULL)
		{
			if (pars.argv[i][0] == '=')
				ft_export_output_err(pars.argv[i]);
			else
				data->envp = ft_env_add(data, pars.argv[i]);
			i++;
		}
		create_index(&(*data));
		sort_mass(data->envp, &data->index, data->size);
	}
	return (0);
}
