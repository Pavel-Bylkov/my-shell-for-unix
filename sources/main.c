#define MAIN_FILE
#include "my_shell.h"


int	main(int argc, char **argv, char **envp)
{
	t_data data;

    g_data = &data;
    init_struct(&data, envp);
	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
	    return (one_run(&data, argv[2]));
	else if (argc == 2)
	    read_from_file(&data, argv[1]);
	else
	    main_loop(&data);
	return (0);
}

int     one_run(t_data *data, char *str)
{
    int error;

    error = 0;
    data->line = g_strdup(str);
    if (data->line == NULL)
        return (0);
    if (check_unexpected_token(data->line) != 0)
        return (2);
    error = parse_line(data, error);
    data->code_exit = run_comands(data, error);
    //print_pars(data);
    g_free(data->line);
    ft_parsclear(&(data->curr_pars));
    //printf("count malloc = %d\n", data->count_malloc);
    //free_struct(data);
    return (data->code_exit);
}

void        read_from_file(t_data *data, char *filename)
{

}
