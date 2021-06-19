#include <stdio.h>
int main(int argc, char **argv)
{
    int i;
    printf("%d\n", argc);
    i = 0;
    while (argv[i])
        printf("%s\n", argv[i++]);
    i = 0;
    printf("%d %d %d\n", 5 || 0, 0 || -5, -5 || 5);
    return (0);
}