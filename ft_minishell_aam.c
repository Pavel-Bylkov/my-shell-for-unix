#include <stdio.h>
#include "includes/my_shell.h"
#include <string.h>


char	*ft_strdup(const char *s)  //! функция Libft
{
	char	*str;
	char	*rez;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	rez = str;
	while (*s)
		*str++ = *(char *)s++;
	*str = *(char *)s;
	return (rez);
}

void	temp_init_pars(t_pars *struc)  //! Временная функция
{
	struc->path = NULL;
	struc->argv = (char **)malloc(sizeof(char *) * 3);
	struc->argv[0] = ft_strdup("echo");
	struc->argv[1] = NULL;
	//struc->argv[1] = ft_strdup("ddd'ddd");
	//struc->argv[2] = NULL;

}

void	init_data(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i));
	data->index = (int *)malloc(sizeof(int) * (i - 1));
	data->size = i;
	i = -1;
	while (env[++i] != NULL)
	{
		data->envp[i] = ft_strdup(env[i]);
		data->index[i] = i;
	}
	data->envp[i] = NULL;
}

void	swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
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

void	sort_mass(char **mas, int *id[], int size)
{
	int		i;
	int		right;

	right = size - 1;
	while (right > 0)
	{
		i = 0;
		while (i < right)
		{
			if (ft_strcmp(mas[(*id)[i]], mas[(*id)[i + 1]]) > 0)
				swap(&((*id)[i]), &((*id)[i + 1]));
			i++;
		}
		right--;
	}
}

int		aam_main(t_data *data)
{
	//t_pars		pars;
	//t_data		data;
	//int			i;

	//temp_init_pars(&pars);
	//init_data(env, &data);

	//i = 0;
	//printf("..\n..\n");
	//while (i < data.size)
	//{
	//	printf("%d - %s\n", data.index[i], data.envp[data.index[i]]);
	//	i++;
	//}

	//printf("\nsize = %d\n\n", data.size);

	sort_mass(data->envp, &data->index, data->size);
	ft_export(*data, *data->curr_pars);

	//i = -1;
	//while (++i < data.size)
	//	printf("%d - %s\n", data.index[i], data.envp[data.index[i]]);
	return (0);

}
