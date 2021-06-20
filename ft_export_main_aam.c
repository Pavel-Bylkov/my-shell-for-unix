#include "my_shell.h"

int	ft_export(t_data *data, t_pars *pars)
{
	int		i;
	int		code;
	int		pos;

	code = 0;
	if (pars->argv[1] == NULL)
		ft_out_export(*data);
	else
	{
		i = 1;
		while (pars->argv[i] != NULL)
		{
			pos = ft_char_in_str(pars->argv[i], '=');
			if (pars->argv[i][0] == '='
				|| (pars->argv[i][0] >=48 && pars->argv[i][0] <=57)
				|| ft_chrstr_in_set(pars->argv[i], "!@#$%^&*()±<>~{}[]", pos) == 0)
				code = ft_export_output_err(1, pars->argv[i]);
			else
				data->envp = ft_env_add(data, pars->argv[i], &(data->size));
			i++;
		}
		create_index(&(*data));
		sort_mass(data->envp, &data->index, data->size);
	}
	return (code);
}
