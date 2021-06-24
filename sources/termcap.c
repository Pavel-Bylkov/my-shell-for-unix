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
