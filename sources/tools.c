#include "my_shell.h"

int			brackets_is_open(char *str, int n)
{
	int		i[2];

	i[0] = -1;
    i[1] = 0;
	while (str[++i[0]] != '\0' && i[0] < n)
	{
        if (str[i[0]] == '(' && backslash_is_active(str, i[0]) == 0 
				&& quaote_is_open(str, i[0]) == 0)
			++i[1];
        else if (str[i[0]] == ')' && backslash_is_active(str, i[0]) == 0 
				&& quaote_is_open(str, i[0]) == 0)
			--i[1];
	}
	return (i[1]);
}

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
		printf("count : %d\n", tmp->count);
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
	free_array((void **)data->index);
}

void	g_free(void *content)
{
	if (content != NULL)
	{
		free(content);
		content = NULL;
	}
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

char	*g_newpath(char *dir, int n, char *name)
{
	char	*res;
	char	*tmp;
	char	*dir_tmp;

	dir_tmp = ft_strdupn(dir, n);
	tmp = ft_strjoin(dir_tmp, "/");
	res = ft_strjoin(tmp, name);
	g_free(dir_tmp);
	g_free(tmp);
	return (res);
}
