#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	char_c;

	if ((b == NULL && len == 0))
		return (NULL);
	ptr = (unsigned char *)b;
	char_c = (unsigned char)c;
	while (len-- != 0)
	{
		if (*ptr == char_c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
