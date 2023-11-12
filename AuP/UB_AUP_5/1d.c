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

void ausgabeformat(double **ipp, int column, int row)
{

    for (unsigned int i = 0; i < column; i++)
    {
        printf("|");
        for (unsigned int j = 0; j < row; j++)
        {

            printf("%.1lf ", ipp[i][j]);
        }
        printf("|");
        printf("\n");
    }
}

int MatrixCheck(int column1, int row1, int column2, int row2)
{
    if (column1 != column2)
    {
        printf("I cant do that exited with 1\n");
        return 1;
    }

    if (row1 != row2)
    {
        printf("I cant do that exited with 1\n");
        return 1;
    }

    return 0;
}

double **sum(double **a, double **b, int column, int row)
{
    double **sumM = func(column, row);

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
        {

            sumM[i][j] = a[i][j] + b[i][j];
        }
    }

    return sumM;
}
// -------------------------------------------------------------
// -------------------------------------------------------------
// M

int main()
{

    int column;
    int row;
    printf("Num of Columns Matrix 1\n");
    scanf("%d", &column);
    printf("Num of Rows Matix 1\n");
    scanf("%d", &row);

    int column2;
    int row2;
    printf("Num of Columns Matrix 2\n");
    scanf("%d", &column2);
    printf("Num of Rows Matrix 2\n");
    scanf("%d", &row2);


    if (MatrixCheck(column, row, column2, row2) == 1)
    {
        return 1;
    }


    double **ipp = func(column, row);

    printf("1 Matrix Inputs\n");
    eingabe(ipp, column, row);
    ausgabeformat(ipp, column, row);

    double **ipp2 = func(column, row);

    printf("2 Matrix Inputs\n");
    eingabe(ipp2, column, row);
    ausgabeformat(ipp2, column, row);

    printf("Result\n");
    double **ipp3 = sum(ipp, ipp2, column, row);
    ausgabeformat(ipp3, column, row);

    freethecalloc(ipp, row);
    freethecalloc(ipp2, row);
    freethecalloc(ipp3, row);
}