#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	if (start < ft_strlen((char *)s))
	{
		tmp = res;
		while (s[start] && len-- != 0)
			*tmp++ = s[start++];
		*tmp = '\0';
	}
	else
		res[0] = '\0';
	return (res);
}
