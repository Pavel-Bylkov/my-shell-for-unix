#include "my_shell.h"

int			ft_stdin_active(char *str, t_data *data)
{
	int		i[2];

	i[0] = -1;
    i[1] = 0;
	while (str[++i[0]] != '\0')
	{
        if (ft_strncmp(&str[i[0]], "<<", 2) == 0 && backslash_is_active(str, i[0]) == 0 
				&& quaote_is_open(str, i[0]) == 0)
			i[1]++;
	}
	i[1] -= tmp_files_size(data->tmp_files);
	return (i[1]);
}

char		*get_end_input(char *str, t_data *data)
{
	char	*end_input;
	int		n_files;
	int		i[2];

	n_files = tmp_files_size(data->tmp_files);
	i[0] = -1;
    i[1] = -1;
	while (str[++i[0]] != '\0' && i[1] < n_files)
	{
        if (ft_strncmp(&str[i[0]], "<<", 2) == 0 && backslash_is_active(str, i[0]) == 0 
				&& quaote_is_open(str, i[0]) == 0)
			i[1]++;
		while (i[1] == n_files && (str[i[0]] == ' ' || str[i[0]] == '<'))
			i[0]++;
	}
	i[1] = i[0] - 1;
	while (str[i[1]] && (str[i[1]] != ' ' || (quaote_is_open(str, i[1]) != 0
			|| backslash_is_active(str, i[1]) != 0)))
		i[1]++;
	end_input = g_strdupn(&str[i[0] - 1], i[1] - i[0] + 1);
	return (quaote_backslash_clean(end_input));
}

char		*get_filename(t_data *data)
{
	int		n_files;
	char	*nbr;
	char	*fname;

	n_files = tmp_files_size(data->tmp_files) + 1;
	nbr = ft_itoa(n_files);
	if (nbr != NULL)
		g_data->count_malloc += 1;
	nbr = g_strjoin(g_strdup("."), 0, 0, nbr);
	fname = g_strjoin(nbr, 0, 0, g_strdup("_tmp_redir.tmp"));
	return (fname);
}

int		read_tmp_stdin(t_data *data, char *str)
{
	t_tmp_files	*new;
	char	*line;
	char	*end_input;
	char	*rez;
	char	*fname;
	int		fd;

	signal(SIGINT, int_handler2);
	line = readline(QUAOTE_PROMT);
	if (line != NULL)
		g_data->count_malloc += 1;
	else
		write(1, "\n", 1);
	rez = g_strdup("");
	end_input = get_end_input(str, data);
	while (line && end_input && ft_strcmp(line, end_input) != 0) // проверить на ^D ^C
	{
		if (rez[0] == '\0')
			rez = g_strjoin(rez, 0, 0, line);
		else
			rez = g_strjoin(rez, 0, 1, line);
		line = readline(QUAOTE_PROMT);
		if (line != NULL)
			g_data->count_malloc += 1;
		else
			write(1, "\n", 1);
	}
	if (line)
		g_free(line);
	g_free(end_input);
	fname = get_filename(data);
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd > 0)
	{
		write(fd, rez, ft_strlen(rez));
		write(fd, "\n", 1);
		new = tmp_files_new(data->count_files + 1, fname);
		if (new != NULL)
			g_data->count_malloc += 1;
		tmp_files_add_back(&(data->tmp_files), new);
		close(fd);
		data->count_files += 1;
	}
	else
		g_free(fname);
	g_free(rez);
	return (0);
}

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

void	g_tmp_files_clear(t_tmp_files **lst)
{
	t_tmp_files	*head;
	t_tmp_files	*tmp;

	if (*lst != NULL)
	{
		head = *lst;
		unlink(head->fname);
		g_free(head->fname);
		head = head->next;
		g_free(*lst);
		while (head != NULL)
		{
			tmp = head->next;
			unlink(head->fname);
			g_free(head->fname);
			g_free(head);
			head = tmp;
		}
		*lst = NULL;
	}
}

t_tmp_files	*tmp_files_new(int index, char *fname)
{
	t_tmp_files	*new;

	new = (t_tmp_files *)malloc(sizeof(t_tmp_files));
	if (new == NULL)
		return (NULL);
	new->index = index;
	new->fname = fname;
	new->next = NULL;
	return (new);
}

int		tmp_files_size(t_tmp_files *lst)
{
	t_tmp_files	*cur;
	int		n;

	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (1);
	n = 1;
	cur = lst;
	while (cur->next != NULL)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}

void	tmp_files_add_back(t_tmp_files **lst, t_tmp_files *new)
{
	t_tmp_files	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

char		*get_filename_by_index(t_tmp_files *head, int index)
{
	t_tmp_files *tmp;

	if (head == NULL)
		return (NULL);
	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->index == index)
			return (tmp->fname);
		tmp = tmp->next;
	}
	return (NULL);
}