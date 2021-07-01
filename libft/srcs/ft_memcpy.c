#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr;
	unsigned char	*srcp;

	if (len == 0 || dst == src)
		return (dst);
	if ((dst == NULL && len == 0) || (dst == NULL && src == NULL))
		return (NULL);
	ptr = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	while (len-- != 0)
		*ptr++ = *srcp++;
	return (dst);
}
