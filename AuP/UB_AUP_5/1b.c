#include <stdlib.h>
#include <stdio.h>

// -------------------------------------------------------------
// -------------------------------------------------------------

/*Task
b) Schreiben Sie eine Funktion, die das soeben dynamisch erzeugte Feld mit Nutzerein-
gaben befüllt.
*/

// -------------------------------------------------------------
// -------------------------------------------------------------

double **func(int colum, int row)
{

    double **ipp;                          // pointer auf einen pointer
    ipp = calloc(colum, sizeof(double *)); // Allocating in heap, addressing location via ipp, Colums are made (these Colums point to another allocated place)
    for (int i = 0; i < colum; i++)        // Each colum point to another row in heap
    {
        ipp[i] = calloc(row, sizeof(double));
    }
    return ipp;
}

void eingabe(double **ipp, int colum, int row)
{
    int h, z = 0;
    int *i = &h;
    int *j = &z;

    while (*i < colum)
    {

        while (*j < row)
        {
            double temp = 0;
            scanf("%lf", &temp);
            ipp[*i][*j] = temp;
            printf("at [%d][%d] =%f\n", *i, *j, ipp[*i][*j]);
            *j++;
        }

        *i++;
    }

    /*
        for (*i = 0; *i < colum; *i + 1)
        {


            for (int j = 0; j < row; j++)
            {
                double temp = 0;

                scanf("%lf", &temp);

                ipp[*i][j] = temp;
                printf("at [%d][%d] =%f\n", *i, j, ipp[*i][j]);
            }

        }
        return;
        */
}

// -------------------------------------------------------------
// -------------------------------------------------------------
// M

int main()
{

    int colum = 0;
    int row = 0;
    printf("Colum\n");
    scanf("%d", &colum);
    printf("Row\n");
    scanf("%d", &row);

    double **ipp = func(colum, row);

    eingabe(ipp, colum, row);
}