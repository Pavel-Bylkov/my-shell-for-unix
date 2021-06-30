#include <dirent.h>
#include "my_shell.h"

int		teamplate_cmp(char *temp, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (temp[i] && str[j])
	{
		while (temp[i + 1] && temp[i] == '*' && temp[i + 1] == '*')
			i++;
		while (str[j] && temp[i] == '*' && temp[i + 1] != str[j])
			j++;
		if (temp[++i] != str[j])
			return (temp[i] - str[j]);
	}
	return (0);
}

int		get_files(char *arg)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");
	(void)arg;
	if (dir == NULL)
		return (ft_perr(NULL, 2, NULL, "couldn't open '.'"));
	else
	{
		puts("contents of root:");
		entry = readdir(dir);
		while (entry != NULL)
			printf("  %s\n", entry->d_name);
		closedir(dir);
	}
	return (0);
}
