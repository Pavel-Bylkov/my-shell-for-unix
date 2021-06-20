#include <stdlib.h>
#include <stdio.h>

int	ft_chrstr_in_set(char *str, char *set)
{
	int		i;
	int		j;

	j = 0;
	while (set[j])
	{
		i = 0;
		while (str[i] != '\0')
			if (str[i++] == set[j])
				return (0);
		j++;
	}
	return (-1);
}

int	main()
{
	char *str = "jffghkfmvkdfj;fkvf";
	if (ft_chrstr_in_set(str, "!@#$%^&*()±<>~{}[]") == 0)
		printf("YES\n");
	else
		printf("NO\n");
}
