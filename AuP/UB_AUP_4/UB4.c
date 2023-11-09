#include <stdlib.h>
#include <stdio.h>

// 1)   a)
char kleinbuchstabenausgabe(char an)
{

    if (an == 123)
    {
        return an;
    }
    else
    {
        printf("%d=%c\n", an, an);
        return kleinbuchstabenausgabe(an + 1);
    }
}

/*2)b)
// In der Integer Funktion
//
/*
int readInteger(){
    int i;
    scanf("%d", &i);
    return i;
}

// wird eine variable i deklariert, welche einen eingabewert zu i zuweist und als funktionswert zuruckgiebt.

        26 , 18 , 18 , 26
        c=a -> a= a+c = 26
        b* -> b -> ad c -> 13 // b*= b* + 4 = 17
        val c= 17+1 = 18
        ad b* ->  val b -> ad c -> 18
        val d = ad a
        ad d* -> val d -> ad a -> val 26
*/

// 2)c)
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 2)d)
int sort(int *a, int *b, int *c)
{

    if (*a > *b)
    {
        swap(a, b);
    }
    if (*a > *c)
    {
        swap(a, c);
    }
    if (*b > *c)
    {
        swap(b, c);
    }
}

// 2)e)
int sum(int z, int *a, int *b)
{

    if (z == 1)
    {
        *b += 1;
        *a += 1;
        return *a, *b;
    }
    else if (z % 2 == 0)
    {
        return *a += z, sum(z - 1, a, b);
    }
    else
    {
        return *b += z, sum(z - 1, a, b);
    }
}

// 3)a)b)c)
// fuer b einfach int k weg deleten und mit n-1 ersetzen bzw. umgedreht

int tollesarray(int mem[100], int n, int k)
{

    if (n == 0)
    {
        return 0;
    }
    else
    {
        scanf("%d\n", &mem[0 + k]);
        return mem[0 + k] + tollesarray(mem, n - 1, k + 1);
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

char inttochar(int zahl)
{
    

    if (stellen(zahl) == 1)
    {
        return;
    }

    int digit = zahl % 10;
    char cdigit = '0' + digit;


    return inttochar(zahl / 10);
}

int main()
{
    /* 1)a)
            char an = 97;
            kleinbuchstabenausgabe(an);
            return 0;
        */
    /* 2)c)
         int x = 1;
            int y = 2;
            printf("%d,%d\n",x,y);
            swap(&x,&y);
            printf("%d,%d\n",x,y);
        */
    /* 2)d)
        int a = 3;
        int b = 2;
        int c = 1;
        printf("es wurde %d %d %d eingegeben\n", a, b, c);
        sort(&a,&b,&c);
        printf("es kommt %d %d %d raus\n", a, b, c);
    */
    /* 2)e)
    int z = 5;
    int a = 0;
    int b = 0;
    sum(z,&a,&b);
    printf("%d,%d",a,b);
    */
    /* 3)a)b)c)
    int k = 0;
    int p = 3;
    int dasArray[100];
    int x = tollesarray(dasArray, p, k);
    for (int i = 0; i < p + 1; i++)
    {
        printf("in dasArray[%d] liegt nun die %d\n", i, dasArray[i]);
    }
    printf("summeDesArrays ist %d", x);
*/

    int Zahl = 123;
    inttochar(&Zahl);

    return 0;
}