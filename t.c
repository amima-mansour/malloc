#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *f;
    char *s;

    f = malloc(-111);
    s = malloc(10);
    if (!f)
        printf("NULL\n");
    f = realloc(s, -2);
    if (!f)
        printf("NUUL\n");
    f = calloc(-2, -2);
    if (!f)
        printf("NULL\n");
    return (0);
}
