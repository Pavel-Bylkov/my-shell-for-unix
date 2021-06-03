#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int ac, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	char	c;
	int		n;
	int		i;
	int		j;
	int		status;

	pid1 = fork();
	pid2 = fork();
	if (pid1 != 0)
	{
		if (pid2 != 0)
			c = 'X';
		else
			c = 'Z';
		//printf("n = %d, \t pid = %d, \t ppid = % d \n", n, getpid(), getppid());
		//kill(pid, SIGKILL);
	}
	else
	{
		if (pid2 != 0)
			c = 'Y';
		else
			c = 'W';
		//printf("n = %d, \t pid = %d, \t ppid = % d \n", n, getpid(), getppid());
		//kill(pid, SIGKILL);
	}
	//wait(&status);
	//kill(pid2, SIGKILL);
	printf("%c \n", c);
	return (0);
}
