#include "mshell.h"

char	**ft_free_mas(char **mas)
{
	int		i;

	i = 0;
	while (mas[i] != NULL)
		free(mas[i++]);
	free(mas);
	return (NULL);
}

int	ft_export_join_loop(t_data *data, char *str, char **line, int size)
{
	int		i;
	int		fl;
	int		pos;

	fl = 0;
	i = -1;
	pos = ft_char_in_str(str, '+');
	while (++i < size && fl == 0)
	{
		if (ft_strncmp(data->envp[i], str, pos) == 0
			&& data->envp[i][pos] == '=')
		{
			*line = ft_strjoin(data->envp[i], &str[pos + 2]);
			free(data->envp[i]);
			data->envp[i] = ft_strdup(*line);
			free(*line);
			fl = 1;
		}
	}
	return (fl);
}

void	ft_export_join_aam(t_data *data, char *str, int size)
{
	int		pos;
	char	*line;
	int		fl;

	pos = ft_char_in_str(str, '+');
	fl = ft_export_join_loop(data, str, &line, size);
	if (fl == 0)
	{
		str[pos] = '\0';
		line = ft_strjoin(str, &str[pos + 1]);
		data->envp = ft_env_add(data, line, &(data->size));
		free(line);
	}
}

int	ft_export_loop(t_data *data, t_pars *pars)
{
	int		i;
	int		pos;
	int		code;

	code = 0;
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
						"!@#$%%^&*()±<>~{}[],:/;.?+-", pos) == 0)
				code = ft_export_output_err(1, pars->argv[i]);
			else
				data->envp = ft_env_add(data, pars->argv[i], &(data->size));
		}
	}
	return (code);
}

int	ft_export(t_data *data, t_pars *pars)
{
	int		code;

	code = 0;
	if (pars->argv[1] == NULL)
		ft_out_export(*data);
	else
	{
		code = ft_export_loop(data, pars);
		create_index(&(*data));
		sort_mass(data->envp, &(data->index), data->size);
	}
	return (code);
}
