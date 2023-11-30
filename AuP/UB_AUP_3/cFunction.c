#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//----------------------------------------------------------------------------

int eingabe3Maximum(int a, int b, int c)
{
    if (b<a> c)
        return a;
    else if (b > c)
        return b;
    else
        return c;
};

int RestlosTeilbar(int m, int n)
{

    if (m % n == 0)
        return 1;
    else
        return 0;
}

int sum(int n)
{

    if (n >= 1) // alternativ (n != 1)
    {
        return n + sum(n - 1);
    }
    else
        return n;
}
// != bedeutet ist nicht

int fakult(int x)
{

    if (x == 1 || x == 0)
    {
        return x;
    }
    else
    {

        return x * fakult(x - 1);
    }
}

int queersumme(int q)
{

    if (q == 0)
    {
        return q;
    }
    else
    {

        return q % 10 + queersumme(q / 10);
    }
}

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

int stellenausgabe(int s, int k) // s
{

    if (s <= 9)
    {
        printf("%d\n", s * power(1, k));
        return s;
    }
    else
    {

        printf("%d\n", s * power(1, k));
        k += 1;
        return stellenausgabe(s / 10, k) * power(1, k);
    }
}

//---------------------------------------------------------------------------

int main()
{

    /* Maximum
            int a;
            int b;
            int c;

            printf("Zahl a eingeben: \n");
            scanf("%d", &a);
            printf("Zahl b eingeben: \n");
            scanf("%d", &b);
            printf("Zahl c eingeben: \n");
            scanf("%d", &c);

            int Zahl = eingabe3Maximum(a, b, c);

            if (Zahl == a)
            {
                printf("a ist das Maximum mit %d\n", eingabe3Maximum(a, b, c));
            }
            else if (Zahl == b)
            {
                printf("b ist das Maximum mit %d\n", eingabe3Maximum(a, b, c));
            }
            else
            {
                printf("c ist das Maximum mit %d\n", eingabe3Maximum(a, b, c));
            }
        */

    /* Restlost Teilbar
            int m, n;
            printf("m = ? \n");
            scanf("%d", &m);
            printf("n = ? \n");
            scanf("%d", &n);
            printf("%d\n", RestlosTeilbar(m, n));

            int Answer = RestlosTeilbar(m, n);
            if (Answer == 1)
                printf("m geteilt n ergibt eine zahl ohne rest\n");
            else
                printf("m geteilt n ergibt eine zahl mit rest\n");
        */

    /* Aufaddieren bis n
        int n;

        printf("Bis zu welcher Zahl aufaddieren?\n");
        scanf("%d", &n);
        printf("Aufaddiert bis zu %d ist das ergebniss %d\n",n , sum(n));

    */

    /* Faku

   int x;

    printf("x eingeben damit x!\n");

    scanf("%d", &x);

    printf("= Das ergebniss ist %d = ", fakult(x));

    int callme(int x)
    {
        if (x == 1)
        {
            return 0;
        }
        else
        {

            return printf("%d*", x) && printf("%d, %d = ", fakult(x-1), fakult(x-1)) && callme(x - 1);
        }
    }
    callme(x);
    */

    /* Queersumme

   int q;
   printf("von welcher zahl soll ich die queersumme bilden\n");
   scanf("%d", &q);
   printf("Queersumme von %d ist %d\n",q ,queersumme(q));
*/
    int k = 0;
    int z;
    scanf("%d", &z);
    stellenausgabe(z, k);

    return 0;
}