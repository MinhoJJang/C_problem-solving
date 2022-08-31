#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char *a, char *b)
{
    return strcmp((char *)a, (char *)b);
}

int main()
{
    char s1[10][9] = {
        "india", "delta", "bravo", "kilo", "alfa",
        "echo", "hotel", "juliet", "golf", "charli"};

    qsort(s1, 10, 9, compare);

    for (int i = 0; i < 10; i++)
    {
        printf("%s ", s1[i]);
    }

    printf("\n");

    return 0;
}