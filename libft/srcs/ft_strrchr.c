#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
		str++;
	while ((size_t)str != (size_t)s - 1)
	{
		if (*str == (char)c)
			return (str);
		str--;
	}
	return (NULL);
}
