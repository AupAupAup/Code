
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------//
//--------------------------------------------------//
/* TASKasw


b) Schreiben Sie eine Funktion, die die ID des Mutterunternehmens mit dem höchsten
gesamten Unternehmenswert (Wert des Mutterunternehmens + Tochterunternehmens)
als Ganzzahl zurückgibt. Die Funktion bekommt ein Array von structs
und die Anzahl der Unternehmen übergeben. Sie können davon ausgehen, dass jedes
Mutterunternehmen nur ein Tochterunternehmen besitzt.

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

int totuw(struct Unternehmen in[], int n, int * ID)
{
    int res = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        double temp = (in[i].Wert + in[i].Tochterunternehmen->Wert);
        double temp2 = (in[i+1].Wert + in[i+1].Tochterunternehmen->Wert);

        if (temp > temp2)
        {
            res = in[i].ID;
        }
        else
        {
            res = in[i+1].ID;
        }
    }
    ID = &res;
    return res;
}

struct person
{
    unsigned int alter;
    double groesse;
};

struct person *personenliste(int n)
{
    printf("How much persons u want\n");
    scanf("%i", &n);
    struct person *p;
    p = (struct person *)malloc(n * sizeof(struct person));
    return p;
}

void eingabepl(struct person *ptper, int n)
{
    for (int i = 0; i < n; ++i)
    {
        scanf("%u %lf", &(i + ptper)->alter, &(ptper + i)->groesse); //
    }
}

double determinlargestpl(struct person *ptper, int n)
{
    double res;
    for (int i = 0; i < n; ++i)
    {
        if (ptper[i].groesse > res)
        {
            res = ptper[i].groesse;
        }
    }
    return res;
}

//--------------------------------------------------//
//--------------------------------------------------//

int main()
{

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

    printf("%d\n", totuw(ab, 3));
}
