#include <stdio.h>
#include <stdlib.h>

int main()
{

    int A[5];

    for (int i = 0; i < 5 /*sizeof(A) / sizeof(A[0])*/; i++)
    {

        A[i] = i + 10;
    }

    printf("%d bytes in  Array\n", sizeof(A));
    printf("ADRESS\n %p, %p, %p, %p, %p, \n\n", &A[0], &A[1], &A[2], &A[3], &A[4]);
    printf("VALUES\n %d, %d, %d, %d, %d, \n\n", A[0], A[1], A[2], A[3], A[4]);

    printf("\n%p, %p , %d\n\n", A, &A, *A);

    printf("ADRESS BUT WITH POINTER ARITHMETIC\n %p, %p, %p, %p, %p, \n\n", A, A + 1, A + 2, A + 3, A + 4);
    printf("VALUES BUT WITH POINTER ARITHMETIC\n %d, %d, %d, %d, %d, \n\n", *A, *A + 1, *A + 2, *A + 3, *A + 4);
}