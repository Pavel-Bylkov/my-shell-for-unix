#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		k;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	str = (char *)malloc(i + k + 1);
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		str[i] = s1[i];
	k = 0;
	while (s2 && s2[k])
		str[i++] = s2[k++];
	str[i] = '\0';
	free(s1);
	return (str);
}

int	ft_in_set(char *str, char c)
{
	int		t;

	t = 1;
	if (str == NULL)
		return (0);
	while (str[t - 1] != c && str[t - 1] != '\0')
		t++;
	if (str[t - 1] == '\0')
		t = 0;
	return (t);
}

char	*ft_trim(char *str, int n)
{
	char	*rez;
	int		i;

	i = 0;
	while (str[n + i])
		i++;
	rez = (char *)malloc(i + 1);
	if (!rez)
		return (NULL);
	i = 0;
	while (str[n + i])
	{
		rez[i] = str[n + i];
		i++;
	}
	rez[i] = '\0';
	free(str);
	return (rez);
}
