#include "mshell.h"

void	ft_strcopy_fr(char **line, char *str)
{
	int		k;

	ft_free((void **)line);
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

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char	*ft_g_strdupanychr(char *str, char *end)
{
	char	*dst;
	int		len;

	len = 0;
	while (str[len] && (chr_in_str(str[len], end) == -1
			|| quaote_is_open(str, len) != 0
			|| backslash_is_active(str, len) != 0))
		len++;
	dst = ft_strdupn(str, len);
	return (dst);
}

char	*ft_g_strjoin(char *str1, int n, int k, char *str2)
{
	char	*res;
	char	*tmp;

	if (n == -1)
		str1[ft_strlen(str1) - 1] = '\0';
	if (k == 1)
	{
		tmp = str1;
		str1 = ft_strjoin(str1, "\n");
		ft_free((void **)&tmp);
	}
	res = ft_strjoin(str1, str2);
	ft_free((void **)&str1);
	ft_free((void **)&str2);
	return (res);
}

int	check_number(char *str)
{
	int					i;
	unsigned long long	rez;

	if (((int)ft_strlen(str) > 19 && str[0] != '-')
		|| ft_strcmp(str, "9223372036854775808") == 0
		|| ft_strcmp(str, "9223372036854775809") == 0
		|| (int)ft_strlen(str) > 20)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) || (i == 0 && str[i] == '-'))
			continue ;
		return (-1);
	}
	rez = ft_atoi_llu(str);
	rez = rez % 256;
	if (str[0] == '-')
		return (256 - (int)rez);
	return ((int)rez);
}
