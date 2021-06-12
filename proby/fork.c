#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int ac, char **av, char **envp)
{
	pid_t	pid[3];
	pid_t	pid2;
	int		status;
	char	**arg;
	int		fd[5][2];
	int stat;

	arg = (char **)malloc(sizeof(char *) * 4);
	arg[0] = (char *)malloc(sizeof(char) * 10);
	arg[1] = (char *) malloc(sizeof(char) * 20);
	arg[2] = NULL;

	arg[0] = "echo";
	arg[1] = "Attempt at writing";


	pipe(fd[0]);

	pid[0] = fork();
	if (pid[0] == 0)
	{
		dup2(fd[0][1], 1);
		close(fd[0][0]);
		close(fd[0][1]);
		execve("/bin/echo", arg, envp);
			exit(10);
	}

	pipe(fd[1]);
	pid[1] = fork();
	if (pid[1] == 0)
	{
		char *cmd[] = {"cat", "-e", NULL};

		arg[0] = "cat";
		arg[1] = "-e";

		dup2(fd[0][0], 0);
		dup2(fd[1][1],1);

		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
		execve("/bin/ca", cmd, envp);
		write(2, "qwertgyh\n", 9);
		exit(-10);
	}

	close(fd[0][0]);
	close(fd[0][1]);
	pid[2] = fork();
	if (pid[2] == 0)
	{
		char *cmd[] = {"cat", "-e", NULL};
		arg[0] = "cat";
		arg[1] = "-e";

		dup2(fd[1][0], 0);
		close(fd[1][0]);
		close(fd[1][1]);
		execve("/bin/cat", arg, envp);
		>
		exit(12);

	}

	close(fd[1][0]);
	close(fd[1][1]);
	int h = -1;
	stat = 0;
	while (stat == 0 && ++h < 3)
	{
		waitpid(pid[h], &stat, 0);
		stat = WEXITSTATUS(stat);
		printf("h = %d\n", h);
	}
	printf("stats %d\n", stat);
	printf("Ok\n");
	//while (1);
	return (0);
}
