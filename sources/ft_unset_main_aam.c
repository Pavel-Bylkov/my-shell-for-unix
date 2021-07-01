#include "mshell.h"

int	ft_unset_truefalse(t_pars pars, int i)
{
	if ((ft_char_in_str(pars.argv[i], '=')
			!= (int)ft_strlen(pars.argv[i]))
		|| (pars.argv[i][0] >= 48 && pars.argv[i][0] <= 57)
		|| ft_chrstr_in_set(pars.argv[i],
			"!@#$%%^&*()±<>~{}[],:/;.?+-=", ft_strlen(pars.argv[i])) == 0)
		return (1);
	else
		return (0);
}

int	ft_unset(t_data *data, t_pars pars)
{
	int		i;
	int		code;

	code = 0;
	if (pars.argv[1] != NULL)
	{
		i = 1;
		while (pars.argv[i] != NULL)
		{
			if (ft_unset_truefalse(pars, i))
			{
				ft_unset_output_err(pars.argv[i]);
				code = 1;
			}
			else
				data->envp = ft_env_del(data, pars.argv[i], &(data->size));
			i++;
		}
		create_index(&(*data));
		sort_mass(data->envp, &data->index, data->size);
	}
	return (code);
}
