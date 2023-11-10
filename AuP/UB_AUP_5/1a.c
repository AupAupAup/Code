#include <stdlib.h>
#include <stdio.h>

// -------------------------------------------------------------
// -------------------------------------------------------------

/*Task

Aufgabe 1
a) Schreiben Sie eine Funktion, die eine anonyme Variable für ein zwei-dimensionales
Feld vom Typ double dynamisch erzeugt und zurückgibt. Die Anzahlen der Zeilen
und Spalten werden als Parameter übergeben.
*/

// -------------------------------------------------------------
// -------------------------------------------------------------


double **func(int colum, int row)
{

    double **ipp; //pointer auf einen pointer
    ipp = calloc(colum, sizeof(double *)); // Allocating in heap, addressing location via ipp, Colums are made (these Colums point to another allocated place)
    for (int i = 0; i < colum; i++) // Each colum point to another row in heap
    {
        ipp[i] = calloc(row, sizeof(double));
    }
    return ipp;
}



// -------------------------------------------------------------
// -------------------------------------------------------------
// M

int main(void)
{

    int colum;
    int row;

    scanf("%d", &colum);
    scanf("%d", &row);
    func(colum, row);
}