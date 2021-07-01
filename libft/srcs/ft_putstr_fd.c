#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void	ft_putstrn_fd(char *s, size_t len, int fd)
{
	if (s != NULL)
		write(fd, s, len);
}
