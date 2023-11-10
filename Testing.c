

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

int main()
{
double temp = 0;

            scanf("%lf", &temp);
            printf("check\n");
            printf("check number = %lf\n",temp);
            
}