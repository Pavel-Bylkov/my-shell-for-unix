#include <stdio.h>
int main(int argc, char **argv)
{
    int i;
    printf("%d\n", argc);
    i = 0;
    while (argv[i])
        printf("%s\n", argv[i++]);
    i = 0;
    return (0);
}