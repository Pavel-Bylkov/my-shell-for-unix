#include "my_shell.h"

void	ft_new_list(t_history **list, char *str, int len)
{
	int		j;

	*list = (t_history *)malloc(sizeof(t_history));
	j = 0;
	(*list)->line = (char *)malloc(sizeof(char) * len);
	while (str[j] != '\0')
	{
		(*list)->line[j] = str[j];
		j++;
	}
	(*list)->line[j] = '\0';
	(*list)->next = NULL;
	(*list)->prev = NULL;
}

void	ft_add_list(t_history **list, char *str, int len)
{
	t_history	*temp;
	int			j;

	temp = (t_history *)malloc(sizeof(t_history));
	j = 0;
	temp->line = (char *)malloc(sizeof(char) * len + 1);
	while (str[j] != '\0')
	{
		temp->line[j] =  str[j];
		j++;
	}
	temp->line[j] = '\0';
	temp->prev = NULL;
	temp->next = (*list);
	temp->next->prev = temp;
	(*list) = temp;
}

t_history	*ft_hist_create(t_history *hist, int fd_hist)
{

	return (hist);
}

void	ft_change_struct(t_history **list, char *str)
{
	int		k;

	k = ft_strlen(str);
	free ((*list)->line);
	(*list)->line = (char *)malloc(sizeof(char) * k + 2);
	k = 0;
	while (str[k] != '\0')
	{
		(*list)->line[k] = str[k];
		k++;
	}
	(*list)->line[k] = '\0';
}

void	ft_last_in_struct(t_history **list, char *str)
{
	int		k;

	k = ft_strlen(str);
	while ((*list)->prev != NULL)
		*list = (*list)->prev;
	free ((*list)->line);
	(*list)->line = (char *)malloc(sizeof(char) * k + 2);
	k = 0;
	while (str[k] != '\0')
	{
		(*list)->line[k] = str[k];
		k++;
	}
	(*list)->line[k] = '\0';
}