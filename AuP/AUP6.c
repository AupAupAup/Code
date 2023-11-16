
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



*/
//--------------------------------------------------//
//--------------------------------------------------//

struct person
{
    unsigned int alter;
    double groesse;
};

struct person *personenliste(int n)
{
    int n;
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
        scanf("%u %lf", (ptper + i)->alter, (ptper + i)->groesse); // watum geht *(ptper + 1).alter; nicht ?
    }
}

double determinlargest(struct person *ptper, int n)
{
    double res;
    for (int i = 0; i < n; ++i)
    {       
        if ((ptper + n)->groesse > res)
        {
            res = (ptper + n)->groesse;
        }
    }
    return res;
}

struct Unternehmen {
    int ID;
    double Wert;
    struct Unternehmen* Tochterunternehmen;
};


//--------------------------------------------------//
//--------------------------------------------------//

int main()
{
}