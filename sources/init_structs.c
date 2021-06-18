#include "my_shell.h"

void        init_struct(t_data *data, char **envp)
{
    data->line = NULL;
    data->tmp_files = NULL;
    data->count_files = 0;
    data->curr_pars = NULL;
    data->errors = NULL; //errors_create();
	data->code_exit = 0;
    data->count_malloc = 0;
    init_data(envp, data);
    init_pwd_aam(data);
}

