#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char **env)
{
	char **av;

	av = (char **)malloc(sizeof(char *) * 3);
	av[0] = strdup("binar");
	av[1] = strdup("fghj  lkfglkf   lfkgldkg");
	av[2] = NULL;

	execve("binar", av, NULL);
}
