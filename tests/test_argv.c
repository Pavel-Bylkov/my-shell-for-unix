#include <stdio.h>

int	teamplate_cmp(char *temp, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (temp[i] && str[j])
	{
        while (temp[i + 1] && temp[i] == '*' && temp[i + 1] == '*')
			i++;
        if (temp[i] == '*' && temp[i + 1] == '\0')
            break ;
		while (str[j] && temp[i] == '*' && temp[i + 1] != str[j])
			j++;
        if (temp[i] == '*' && temp[i + 1] == str[j])
            i += 2 + 0 * j++;
        else if (temp[i] == str[j])
            (void)(i++ + j++);
		else
			return (temp[i] - str[j]);
	}
	return (0);
}

int main(int argc, char **argv)
{
    int i;
    printf("%d\n", argc);
    i = 0;
    while (argv[i])
        printf("%s\n", argv[i++]);
    i = 0;
    printf("tom.txt & t*txt = %d\n", teamplate_cmp("t*txt", "tom.txt"));
    printf("tom.txt & *txt = %d\n", teamplate_cmp("*txt", "tom.txt"));
    printf("tom.txt & t* = %d\n", teamplate_cmp("t*", "tom.txt"));
    printf("tom.txt & a* = %d\n", teamplate_cmp("a*", "tom.txt"));
    printf("tom.txt & * = %d\n", teamplate_cmp("*", "tom.txt"));
    printf("tom.txt & t*t = %d\n", teamplate_cmp("t*t", "tom.txt"));
    printf("tom.txt & *t*t = %d\n", teamplate_cmp("*t*t", "tom.txt"));
    printf("tom.txt & tom.txt* = %d\n", teamplate_cmp("tom.txt*", "tom.txt"));
    printf("tom.txt & tom*.txt = %d\n", teamplate_cmp("tom*.txt", "tom.txt"));
    return (0);
}