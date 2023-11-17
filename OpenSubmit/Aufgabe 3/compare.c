#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int temp;
    temp = atoi(argv[1]);
    int secin;
    scanf("%d", &secin);

    if (secin > temp)
    {
        printf("%d > %d\n", secin, temp);
        return secin;
    }
    else if(secin < temp)
        {
            printf("%d < %d\n", secin, temp);
        } else { printf("%d = %d\n", secin, temp);}
}