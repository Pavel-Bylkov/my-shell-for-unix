#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*src;
	size_t	len;
	char	*dst;
	char	*strcp;

	src = (char *)str;
	len = ft_strlen(src);
	dst = (char *)malloc(len + 1);
	if (NULL == dst)
		return (NULL);
	strcp = dst;
	while (len-- != 0)
		*strcp++ = *src++;
	*strcp = '\0';
	return (dst);
}

char	*ft_strdupn(const char *str, size_t len)
{
	char	*src;
	char	*dst;
	char	*strcp;

	src = (char *)str;
	dst = (char *)malloc(len + 1);
	if (NULL == dst)
		return (NULL);
	strcp = dst;
	while (len-- != 0 && *src)
		*strcp++ = *src++;
	*strcp = '\0';
	return (dst);
}
