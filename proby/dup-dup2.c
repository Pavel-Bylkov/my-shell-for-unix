#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	int		old_fd;
	char	buffer[10];
	int		i;

	i = 7;
	fd = open("text.txt", O_CREAT | O_RDWR, 0666);
	//old_fd = open("text.txt", O_WRONLY, 0666);
	//printf ("old_fd = %d,  fd = %d \n", old_fd, fd);
	while (i>=0)
	{
	//old_fd = dup(fd);
	//old_fd = fd;
		read(fd, buffer, 1);
		printf("'%s' \n", buffer);
		write(fd, buffer, 1);
		i--;
	}
	close (fd);
	close (old_fd);
	return (0);
}
