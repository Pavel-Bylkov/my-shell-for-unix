#include "my_shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	int error;

	(void)argc;
	(void)argv;
	init_struct(&data, envp);
	error = main_loop(&data);
	close(data.fd_hist);
	free_struct(&data);
	return (error);
}
