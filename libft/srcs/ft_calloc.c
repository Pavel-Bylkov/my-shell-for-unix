#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	unsigned char	*ptr;
	size_t			len;

	len = number * size;
	ptr = (unsigned char *)malloc(len);
	if (NULL == ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return ((void *)ptr);
}
