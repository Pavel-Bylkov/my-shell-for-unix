#include <stdio.h>
#include "includes/my_shell.h"
#include <string.h>


//char	*ft_strdup(const char *s)  //! функция Libft
//{
//	char	*str;
//	char	*rez;
//	size_t	i;

//	i = 0;
//	while (s[i])
//		i++;
//	str = (char *)malloc(i + 1);
//	if (str == NULL)
//		return (NULL);
//	rez = str;
//	while (*s)
//		*str++ = *(char *)s++;
//	*str = *(char *)s;
//	return (rez);
//}

void	temp_init_pars(t_pars *struc)  //! Временная функция
{
	struc->path = NULL;
	struc->argv = (char **)malloc(sizeof(char *) * 5);
	//struc->argv[0] = ft_strdup("export");
	//struc->argv[1] = ft_strdup("2ddd'ddd");
	//struc->argv[2] = ft_strdup("tt");
	//struc->argv[3] = ft_strdup("tt=58");
	//struc->argv[4] = NULL;

	struc->argv[0] = ft_strdup("unset");
	struc->argv[1] = ft_strdup("4USER");
	struc->argv[2] = ft_strdup("tt=58");
	struc->argv[3] = ft_strdup("Apple_PubSub_Socket_Render");
	struc->argv[4] = NULL;



}

void	create_index(t_data *data)
{
	int		i;

	if (data->index != NULL)
		free(data->index);
	data->index = (int *)malloc(sizeof(int) * (data->size));
	i = -1;
	while (++i < data->size)
		data->index[i] = i;
}


void	init_data(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 1));
	data->index = (int *)malloc(sizeof(int) * (i));
	data->size = i;
	i = -1;
	while (env[++i] != NULL)
		data->envp[i] = ft_strdup(env[i]);
	data->envp[i] = NULL;

	create_index(&(*data));


	//data->index = (int *)malloc(sizeof(int) * data->size);

}

void	swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
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

int		ft_choice_command_aam(t_data *data)
{
	if (data->curr_pars->path == NULL)
	{
		if (!ft_strcmp(data->curr_pars->argv[0], "export"))
			ft_export(data, *data->curr_pars);
		else if (!ft_strcmp(data->curr_pars->argv[0], "unset"))
			ft_unset(data, *data->curr_pars);
	}
	return (0);
}

int		aam_main(t_data *data)
{
	//t_pars		pars;
	//t_data		data;
	int			i;

	data->curr_pars = (t_pars *)malloc(sizeof(t_pars)); //! временное

	temp_init_pars(data->curr_pars); //! временное

	i = -1;
	printf("..\n..\n");
	//printf("\nsize = %d\n\n", data->size);
	//while (++i < data->size)
	//	printf("%d - %s\n", data->index[i], data->envp[data->index[i]]);

	//printf("\nsize = %d\n\n", data->size);

	sort_mass(data->envp, &data->index, data->size);
	ft_choice_command_aam(data);
	//data->curr_pars->argv[1] = NULL;
	//printf("\n%s\n", data->curr_pars->argv[1]);
	//ft_choice_command_aam(data);

	//i = -1;
	//while (++i < data->size)
	//	printf("%d - %s\n", data->index[i], data->envp[data->index[i]]);

	printf("\nsize = %d\n\n", data->size);

	i = -1;
	while (++i < data->size)
		printf("%d - %s\n",i, data->envp[i]);

	while (1);

	return (0);

}
