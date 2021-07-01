#include "libft.h"

size_t	ft_strlcat(char *dst, const	char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen((char *)src);
	len_dst = ft_strlen(dst);
	i = 0;
	n = len_dst;
	if (len_dst < (dstsize - 1) && dstsize > 0)
	{
		while (src[i] && len_dst + i < (dstsize - 1))
			dst[n++] = src[i++];
		dst[n] = 0;
	}
	if (len_dst >= dstsize)
		len_dst = dstsize;
	return (len_dst + len_src);
}
