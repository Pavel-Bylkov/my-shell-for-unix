#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*result;

	result = (unsigned char *)dest;
	if (len > 0)
	{
		while (len-- != 0)
			*result++ = c;
	}
	return (dest);
}
