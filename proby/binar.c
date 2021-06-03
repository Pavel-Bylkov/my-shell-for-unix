#include <stdio.h>
#include "../includes/my_shell.h"

int		ft_strlen(char *str)
{
	int l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

int main(int argc, char *argv[], char **env)
{
	write(0, argv[1], ft_strlen(argv[1]));
	printf("\nlen = %d\n", ft_strlen(argv[1]));
	return (0);
}
