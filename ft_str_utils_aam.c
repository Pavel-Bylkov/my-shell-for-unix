#include "my_shell.h"

char		*ft_strcpy_fr(char *str1, char *str2)
{
	int		i;
	int		len;
	char	*line;

	if (str1 == NULL)
		return (NULL);
	else
		len = ft_strlen(str1);
	if (str2 == NULL)
		return (str1);
	else
		len += ft_strlen(str2) + 1;
	line = (char *)malloc(sizeof(char) * len);
	if (line == NULL)
		return (NULL);
	i = -1;
	while (str1[++i] != '\0')
		line[i] = str1[i];
	while (*str2 != '\0')
		line[i++] = *str2++;
	line[i] = '\0';
	if (str1)
		free(str1);
	return (line);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	str1;
	unsigned char	str2;
	if (s1 == NULL && s2 != NULL)
		return (-1);
	else if (s1 != NULL && s2 == NULL)
		return (1);
	else if (s1 == NULL && s2 == NULL)
		return (0);
	else
	{
		str1 = (unsigned char)*s1;
		str2 = (unsigned char)*s2;
		while (str1 != '\0' && str2 != '\0')
		{
			if (str1 != str2)
				return (str1 - str2);
			str1 = (unsigned char)(*(++s1));
			str2 = (unsigned char)(*(++s2));
		}
		return (str1 - str2);
	}
}

int		ft_char_in_str(char *str, char c) //* проверяет входит ли символ в строку и возвращает номер ее позиции, длину str если не входит
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}
