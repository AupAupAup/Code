

#include <stdlib.h>
#include <stdio.h>

int power(int p, int e)
{

    if (e == 0)
    {
        return p;
    }

    else
    {
        return power(p * 10, e - 1);
    }
}

int stellen(int zahl)
{

    if (zahl == 0)
    {
        return 0;
    }
    else
    {
        return stellen(zahl / 10) + 1;
    }
}

int main(int argc, char *argv[])
{

    printf("%c\n", argv[3][0]);

    int i = 0;
    for (char c = '\0'; c != argv[3][i]; ++i);
    printf("%d",i);
}