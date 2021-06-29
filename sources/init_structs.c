#include "my_shell.h"

void	init_struct(t_data *data, char **envp)
{
	data->line = NULL;
	data->tmp_files = NULL;
	data->count_files = 0;
	data->index = NULL;
	data->curr_pars = NULL;
	data->code_exit = 0;
	init_data(envp, data);
	init_pwd_aam(data);
	data->tmp_fcpec = NULL;
	data->tmp_out = NULL;
}
