#include "my_shell.h"

char	*ft_del_symbol_aam(char *str, int i) //? Удаление i-го символа
{
	char	*s;
	int		k;

	k = ft_strlen(str);
	s = (char *)malloc(sizeof(char) * k);
	k = 0;
	while (k < i - 1)
	{
		s[k] = str[k];
		k++;
	}
	while (str[k + 1] != '\0')
	{
		s[k] = str[k + 1];
		k++;
	}
	s[k] = '\0';
	//free(str);
	return (s);
}

char	*ft_shift_str_aam(char *str, int pos)
{
	int		i;
	char	*newstr;

	i = ft_strlen(str) - pos;
	newstr = (char *)malloc(sizeof(char) * (i + 1));

	i = pos + 2;
	while (str[++i])
	{
	printf("%c\n", str[i]);
		newstr[i - pos - 3] = str[i];
	}
	newstr[i - pos - 3] = '\0';
	return (newstr);
}

void	ft_export_join_aam(t_data *data, char *str, int size)
{
	int		pos;
	int		i;
	char	*line;
	char	*newstr;
	int		fl;
	char	*sss;

	i = -1;
	fl = 0;
	pos = ft_char_in_str(str, '+');
	while (++i < size && fl == 0)
	{
		if (ft_strncmp(data->envp[i], str, pos) == 0 && data->envp[i][pos] == '=')
		{
sss = data->envp[i];
printf("data->envp[i] = %s\n", sss);
			newstr = ft_shift_str_aam(str, pos);
printf("newstr = %s\n", newstr);
			line = ft_strjoin(sss, newstr);
			free(sss);
	printf("afte free data->envp = %s\n", sss);
			data->envp[i] = ft_strdup(line);
			free(newstr);
			free(line);
			fl = 1;
		}
	}
	if (fl == 0)
	{
		line = ft_del_symbol_aam(str, pos + 1);
printf("str = %s\n", str);
		//line = ft_strjoin(str, &str[pos + 1]);
		data->envp = ft_env_add(data, line, &(data->size));
		free(line);
	}

	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
}

int	ft_export(t_data *data, t_pars *pars)
{
	int		i;
	int		code;
	int		pos;

	code = 0;
	if (pars->argv[1] == NULL)
		ft_out_export(*data);
	else
	{
		i = 0;
		while (pars->argv[++i] != NULL)
		{
			pos = ft_char_in_str(pars->argv[i], '+');
			if (pars->argv[i][pos] != '0' && pars->argv[i][pos + 1] == '=')
				ft_export_join_aam(data, pars->argv[i], data->size);
			else
			{
				pos = ft_char_in_str(pars->argv[i], '=');
				if (pars->argv[i][0] == '='
					|| (pars->argv[i][0] >= 48 && pars->argv[i][0] <= 57)
					|| ft_chrstr_in_set(pars->argv[i],
							"!@#$%^&*()±<>~{}[],:/;.?+-", pos) == 0)
					code = ft_export_output_err(1, pars->argv[i]);
				else
					data->envp = ft_env_add(data, pars->argv[i], &(data->size));
			}
		}
		create_index(&(*data));
		sort_mass(data->envp, &data->index, data->size);
	}
	return (code);
}
