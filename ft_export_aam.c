#include "includes/my_shell.h"

char	*ft_strchr(const char *s, int c) //! Libft
{
	//char	sym;

	//sym = c;
	while (*s != '\0')
		if (*s++ == c)
			return ((char *)s - 1);
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

void	ft_out_export(t_data data)
{
	int		i;

	i = -1;
	while (++i < data.size)
	{
		write(1, "declare -x ", 11);
		write(1, data.envp[data.index[i]], ft_strlen(data.envp[data.index[i]]));
		write(1, "\n", 1);
	}
}

int		ft_env_add(t_data data, char *str)
{
	char	**new_env;
	(void)str;

	new_env = (char **)malloc(sizeof(char *) * (data.size + 2));
	(void)new_env;
	return (0);
}

int		ft_export(t_data data, t_pars pars)
{
	int		i;
	if (pars.argv[1] == NULL)
		ft_out_export(data);
	else
	{
		i = 1;
		while (pars.argv[i] != NULL)
		{
			if (ft_strchr(pars.argv[i], '=') == NULL)
				ft_env_add(data, pars.argv[i]);
		}
	}


	return (0);
}
