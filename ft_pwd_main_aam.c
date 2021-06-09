#include "my_shell.h"

int	ft_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	free(dir);
	return (0);
}
