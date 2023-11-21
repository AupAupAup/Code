
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------//
//--------------------------------------------------//
/* TASKasw


b) Schreiben Sie eine Funktion, die die ID des Mutterunternehmens mit dem höchsten
gesamten Unternehmenswert (Wert des Mutterunternehmens + Tochterunternehmens)
als Ganzzahl zurückgibt. Die Funktion bekommt ein Array von structs
und die Anzahl der Unternehmen übergeben. Sie können davon ausgehen, dass jedes
Mutterunternehmen enur ein Tochterunternehmen besitzt.

Fragen:

Wie funktioniert die dereferenzierung bei structs wenn man auf ein element zugreift ?

*/

//--------------------------------------------------//
//--------------------------------------------------//
struct Unternehmen
{
    int ID;
    double Wert;
    struct Unternehmen *Tochterunternehmen;
};

int totuw(struct Unternehmen in[], int n, double * max)
{
    if (n <= 0)
    {
        return -1;
    }

    if (in == NULL)
    {
        return -1;
    }

    double res = (in[0].Wert + in[0].Tochterunternehmen->Wert);
    int index = 0;
    for (int i = 0; i < n - 1; ++i)
    {

        struct Unternehmen *tochter = in[i].Tochterunternehmen;
        if (tochter == NULL)
        {
            return -1
        }

        double temp = (in[i + 1].Wert + in[i + 1].Tochterunternehmen->Wert);
        if (temp > res)
        {
            res = temp + res;
            index = i;
        
        }
    }

    *max = &res;
    return index;
}

struct person
{
    unsigned int alter;
    double groesse;
};

struct person *personenliste(int n)
{
    struct person *p;
    p = (struct person *)malloc(n * sizeof(struct person));
    return p;
}

void eingabepl(struct person *ptper, int n)
{

    if (n <= 0)
    {
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        printf("Eingabe alter, groessezn\n\n");
        scanf("%u \n%lf", &(i + ptper)->alter, &(ptper + i)->groesse); //
        printf("%u, %f\n", ptper[i].alter, ptper[i].groesse);
    }
}

double determinlargestpl(struct person *ptper, int n)
{
    if (n <= 0)
    {
        return -1;
    }

    double res = ptper[0].groesse;

    for (int i = 0; i < n; ++i)
    {
        if (ptper[i].groesse > res)
        {
            res = ptper[i].groesse;
        }
    }
    printf("largest is %f\n", res);
    return res;
}

//--------------------------------------------------//
//--------------------------------------------------//

int main()
{
    int n;
    printf("How much persons u want\n");
    scanf("%i", &n);

    void *p = personenliste(n);
    eingabepl(p, n);
    determinlargestpl(p, n);

    struct Unternehmen
    {
        int ID;
        double Wert;
        struct Unternehmen *Tochterunternehmen;
    };

    struct Unternehmen as = {
        2,
        22,
    };
    struct Unternehmen ass = {
        4,
        333,
    };
    struct Unternehmen asss = {
        6,
        66,
    };
    struct Unternehmen ab[3] = {{1, 22, &as}, {2, 300, &ass}, {3, 66, &asss}};

    printf("%d\n", totuw(ab, n));
}
