#include "my_shell.h"

int	ft_env_output_err(int code, char *str)
{
	write(1, "env: ", 5);
	write(1, str, ft_strlen(str));
	write(1, ": No such file or directory\n", 28);
	return (code);
}

int	ft_export_output_err(int code, char *str)
{
	write(2, "my_shell: export: ", 18);
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (code);
}

int	ft_output_err_aam(int code, char *str1, char *str2, char *str3)
{
	write(2, "my_shell: ", 10);
	if (str1)
		write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	return (code);
}

int	ft_command_err_aam(char *name_f)
{
	struct stat	buff;

	if (name_f[0] == '.' && name_f[1] == '\0')
		return (ft_output_err_aam(1, name_f,
				": filename argument required\n",
				".: usage: . filename [arguments]\n"));
	if (name_f[0] == '.' && name_f[1] == '.' && name_f[2] == '\0')
		return (ft_output_err_aam(127, name_f, ": command not found\n", NULL));
	if (ft_char_in_str(name_f, '/') < (int)ft_strlen(name_f))
	{
		if (opendir(name_f) != NULL)
			return (ft_output_err_aam(126, name_f, ": is a directory\n", NULL));
		else
		{
			if (stat(name_f, &buff) >= 0)
				return (ft_output_err_aam(126, name_f,
						": Permission denied\n", NULL));
			name_f[ft_char_in_str(name_f, '/')] = '\0';
			if (stat(name_f, &buff) >= 0)
				return (ft_output_err_aam(127, name_f,
						": Not a directory\n", NULL));
			return (ft_output_err_aam(127, name_f,
					": No such file or directory\n", NULL));
		}
	}
	if (stat(name_f, &buff) < 0)
		return (ft_output_err_aam(127, name_f,
					": No such file or directory\n", NULL));
	return (ft_output_err_aam(127, name_f, ": command not found\n", NULL));
}
