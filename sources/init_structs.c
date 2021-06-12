#include "my_shell.h"

void        init_struct(t_data *data, char **envp)
{
    data->curr_pars = NULL;
	init_data(envp, data);
    data->line = NULL;
    data->errors = NULL; //errors_create();
    //load_history(data);
	data->code_exit = 0;
    data->count_malloc = 0;
}

