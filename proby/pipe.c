#include<unistd.h>
#include<stdio.h>

int	main()
{
	int		fd[2];
	pid_t	pid;
	int		x;
	int		y;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		x = 10;
		write(fd[1], &x, sizeof(int));
		usleep(500);
		printf("x = %d\n", x);
		read(fd[0], &x, sizeof(int));
		close(fd[0]);
		close(fd[1]);
		printf("new x = %d\n", x);
	}
	else
	{
		read(fd[0], &x, sizeof(int));
		y = x * 10;
		write(fd[1], &y, sizeof(int));
		close(fd[0]);
		close(fd[1]);
		printf("x = %d, y = %d \n", x, y);
	}

	return (0);
}
