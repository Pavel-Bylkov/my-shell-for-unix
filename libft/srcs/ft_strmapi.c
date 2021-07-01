#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	size_t			n;
	size_t			len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen((char *)s);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	n = 0;
	while (n < len)
	{
		res[n] = (*f)(n, s[n]);
		n++;
	}
	res[n] = '\0';
	return (res);
}
