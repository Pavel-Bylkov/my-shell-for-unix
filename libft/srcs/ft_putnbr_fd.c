#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			buf[15];
	long long int	nbr;
	size_t			len;

	len = 14;
	nbr = (long long int)n;
	buf[len--] = '\0';
	if (n < 0)
		nbr = -(long long int)n;
	else if (n == 0)
		buf[len--] = '0';
	while (nbr != 0)
	{
		buf[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		buf[len--] = '-';
	write(fd, &buf[len + 1], 13 - len);
}
