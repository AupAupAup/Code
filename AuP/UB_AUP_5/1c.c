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

double **func(int column, int row)
{

    double **ipp;                           // pointer to pointer
    ipp = calloc(column, sizeof(double *)); // Allocating in heap, addressing location via ipp, Colums are made (these Colums point to another allocated place)
    for (int i = 0; i < column; i++)        // Each colum point to another row in heap
    {
        ipp[i] = calloc(row, sizeof(double));
    }
    return ipp;
}

void eingabe(double **ipp, int column, int row)
{

    for (unsigned int i = 0; i < column; i++)
    {

        for (unsigned int j = 0; j < row; j++)
        {
            double temp = 0;
            scanf("%lf", &temp);

            ipp[i][j] = temp;
            printf("at [%d][%d] =%f\n", i, j, ipp[i][j]);
        }
    }
}

void **freethecalloc(double **ipp, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(ipp[i]);
    }
}

double ausgabeformat(double **ipp, int column, int row)
{

    for (unsigned int i = 0; i < column; i++)
    {
        for (unsigned int j = 0; j < row; j++)
        {
            printf("%.1lf ",ipp[i][j]); 
        }
        printf("\n");
    }
}

// -------------------------------------------------------------
// -------------------------------------------------------------
// M

void main()
{

    int column;
    int row;
    printf("Colum\n");
    scanf("%d", &column);
    printf("Row\n");
    scanf("%d", &row);

    double **ipp = func(column, row);

    eingabe(ipp, column, row);

    ausgabeformat(ipp,column,row);


    freethecalloc(ipp, row);


}