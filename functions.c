#include <stdio.h>

int howmanytimesicandivideuntil0questionmark(int integer)
{
    int k = 0;
    for (k; integer != 0; ++k)
    {
        integer = integer / 2;
    }
    return k;
}

int Stellen2(int power)
{
    if (power == 0)
    {
        return 1;
    }
    for (int i = power; i != 0; --i)
    {
        power *= 10;
    }
    return power;
}

int Stellen1(int power)
{
    if (power == 0)
    {
        return power;
    }
    else
    {
        return Stellen1(power - 1) * 10;
    }
}

int potenziere2(int b, int e)
{
    if (e == 0)
    {
        return 1;
    }
    while (e != 1)
    {
        b *= b;
        --e;
    }
    return b;
}

int potenzieren1(int b, int e)
{
    switch (e)
    {
    case 0:
        return 1;
    case 1:
        return b;
    default:
        return potenzieren1(b, e - 1) * b;
    }
}

int stellen1(int integer)
{
    int count = 0;
    while (integer != 0)
    {
        integer /= 10;
        count += 1;
    }
    return count;
}


int stellen2(int integer)
{
    if (integer == 0)
    {
        return 0;
    }
    else
    {
        return stellen2(integer / 10) + 1;
    }
}

unsigned long long pascal_nk(int n, int k){
    int result = 1;
    int naenner = 1;
    int zaehler = 1;
    if (k > (n-k)){
        for (int i = 1; i < (n-k)+1; i++){
            zaehler = (n - (i-1));
            naenner =(i);
            result = result * zaehler / naenner;
        }
    }
    else{
        for (int i = 1; i < k+1; i++){
            zaehler =(n - (i-1));
            naenner =(i);
            result = result * zaehler / naenner;
        }
    }
    return result;
}

int main(){

unsigned long long a = pascal_nk(465,54);
printf("%lld", a);

}