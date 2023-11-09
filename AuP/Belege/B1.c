

#include <stdlib.h>
#include <stdio.h>

unsigned deldigits(unsigned num, unsigned short div)
{
    if (num == 0)
    {
        return 0;
    }
    if (num % 10 % div == 0)
    {
        return deldigits(num / 10, div);
    }
    return num % 10 + deldigits(num / 10, div) * 10;
}

int main()
{
    int num = 82345672;
    int div = 2;
    printf("%d", deldigits(num, div));
}