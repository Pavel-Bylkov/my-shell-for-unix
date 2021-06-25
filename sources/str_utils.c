#include "my_shell.h"

void	ft_strcopy_fr(char **line, char *str)
{
	int k;

	g_free(*line);
	k = ft_strlen(str);
	*line = (char *)malloc(sizeof(char) * k);
	k = 0;
	while (str[k] != '\0')
	{
		(*line)[k] = str[k];
		k++;
	}
	(*line)[k] = '\0';
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}


char	*g_strdupanychr(char *str, char *end)
{
	char	*dst;
	int		len;

	len = 0;
	while (str[len] && (chr_in_str(str[len], end) == -1 ||
			quaote_is_open(str, len) != 0 
			|| backslash_is_active(str, len) != 0))
		len++;
	dst = ft_strdupn(str, len);
	return (dst);
}

char	*g_strjoin(char *str1, int n, int k, char *str2)
{
	char	*res;
	char	*tmp;

	
	if (n == -1)
		str1[ft_strlen(str1) - 1] = '\0';
	if (k == 1)
	{
		tmp = str1;
		str1 = ft_strjoin(str1, "\n");
		g_free(tmp);
	}
	res = ft_strjoin(str1, str2);
	g_free(str1);
	g_free(str2);
	return (res);
}