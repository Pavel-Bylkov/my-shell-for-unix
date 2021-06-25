#include "my_shell.h"

int	ft_cd_argv(t_pars *pars, t_data *data, char **path)
{
	int		code;

	if (pars->argv[1][0] == '~' && pars->argv[1][1] == '\0')
		*path = ft_path_home(data);
	else if (pars->argv[1][0] == '~' && pars->argv[1][1] != '\0')
		return (ft_output_err_aam(1, pars->argv[1],
				": No such file or directory\n", NULL));
	else if (pars->argv[1] != NULL && pars->argv[1][0] == '-'
		&& ft_strlen(pars->argv[1]) == 1)
	{
		code = ft_path_back(data, path);
		if (code != 0)
			return (code);
	}
	else if (pars->argv[1][0] == '-' && pars->argv[1][1] != '\0')
	{
		pars->argv[1][2] = '\0';
		return (ft_output_err_aam(1, pars->argv[1],
				": invalid option\n", "cd: usage: cd [-L|-P] [dir]\n"));
	}
	else
		*path = ft_strdup(pars->argv[1]);
	return (0);
}

int	ft_cd(t_data *data, t_pars *pars)
{
	int			code;
	char		*path;

	path = NULL;
	if (pars->argv[1] == NULL)
		path = ft_path_home(data);
	else
	{
		code = ft_cd_argv(pars, data, &path);
		if (code != 0)
			return (code);
	}
	if (path)
	{
		code = ft_cd_path(data, &path);
		if (code != 0)
			return (code);
	}
	if (path)
		free(path);
	return (0);
}
