#include "my_shell.h"

void		free_array(void **s)
{
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != NULL)
			g_free(s[i++]);
		g_free(s);
	}
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	print_pars(t_data *data)
{
	t_pars *tmp;
	t_redir *last;
	int		i;

	tmp = data->curr_pars;
	while (tmp != NULL)
	{
		printf("------------------------------------\n");
		printf("error : %d\n", tmp->error);
		printf("path : %s\n", tmp->path);
		printf("argv :\n");
		i = -1;
		while (tmp->argv[++i] != NULL)
			printf("   %d : |%s|\n", i, tmp->argv[i]);
		printf("f_spec : %s\n", tmp->f_spec);
		printf("redirects :\n");
		last = tmp->redirect;
		while (last != NULL)
		{
			printf("   -f_spec : %s\n", last->f_spec);
			printf("   -out : |%s|\n", last->out);
			last = last->next;
		}
		tmp = tmp->next;
	}
	printf("count malloc = %d\n", data->count_malloc);
}

int run_comands(t_data *data, int error)  //! Функция aamarei (моя)
{
	if (error != 0)
		return (error);
    return (aam_main(data));
}

void free_struct(t_data *data)
{
	ft_parsclear(&(data->curr_pars));
	free_array((void **)data->envp);
	g_free(data->line);
	ft_errorsclear(&(data->errors));
	free_array((void **)data->index);
	if (DEBUG)
		printf("count malloc = %d\n", data->count_malloc);
}

void	g_free(void *content)
{
	if (content != NULL)
	{
		free(content);
		g_data->count_malloc -= 1 * DEBUG;
		content = NULL;
	}
}

void	*g_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (NULL != ptr)
		g_data->count_malloc += 1 * DEBUG;
	return (ptr);
}

char	*g_strdup(char *str)
{
	char	*res;

	res = ft_strdup(str);
	if (res != NULL)
		g_data->count_malloc += 1 * DEBUG;
	return (res);
}

char	*g_strdupn(const char *str, size_t len)
{
	char	*dst;

	dst = ft_strdupn(str, len);
	if (NULL != dst)
		g_data->count_malloc += 1 * DEBUG;
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
		if (NULL != str1)
			g_data->count_malloc += 1 * DEBUG;
		g_free(tmp);
	}
	res = ft_strjoin(str1, str2);
	if (NULL != res)
		g_data->count_malloc += 1 * DEBUG;
	g_free(str1);
	g_free(str2);
	return (res);
}

char	*g_newpath(char *dir, int n, char *name)
{
	char	*res;
	char	*tmp;
	char	*dir_tmp;

	dir_tmp = g_strdupn(dir, n);
	tmp = ft_strjoin(dir_tmp, "/");
	if (NULL != tmp)
		g_data->count_malloc += 1 * DEBUG;
	res = ft_strjoin(tmp, name);
	if (NULL != res)
		g_data->count_malloc += 1 * DEBUG;
	g_free(dir_tmp);
	g_free(tmp);
	return (res);
}