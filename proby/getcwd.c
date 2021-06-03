#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
	char		path[50];
	struct stat	buff;
	pid_t		pid;

	getcwd(path, 50);
	printf("Current directory %s\n", path);
	if (stat("fork", &buff) == -1)
		printf("file not found\n");
	else
		printf("size fork.c - %lld\n", buff.st_size);
	pid = fork();
	if (pid == 0)
		execve("fork", NULL, NULL);
	else
	{
		waitpid(pid, NULL, WUNTRACED);
		kill(pid, SIGKILL);
	}
	usleep(2000);
	chdir("/Users/aamarei");
	getcwd(path, 50);
	printf("Current directory %s\n", path);
	return (0);
}
