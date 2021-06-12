#define MAIN_FILE
#include "my_shell.h"


int	main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argc;
	(void)argv;
	g_data = &data;
	init_struct(&data, envp);
	main_loop(&data);
	return (0);
}
