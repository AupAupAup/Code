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

    double **ipp;
    ipp = calloc(colum, sizeof(double *));
    for (int i = 0; i < colum; i++)
    {
        ipp[i] = calloc(row, sizeof(double));
    }
    return ipp;
}

void** freethecalloc (double** ipp, int row) {
        for (int i = 0; i < row; i++)
        {
            free(ipp[i]);
        }
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
    double** ipp = func(colum, row);

}