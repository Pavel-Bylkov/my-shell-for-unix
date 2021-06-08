#include "my_shell.h"

int	ft_env(t_data *data, t_pars pars)
{
	if (pars.argv[1] != NULL)
		ft_env_output_err(pars.argv[1]);
	else
		ft_env_output(data);
	return (0);
}
