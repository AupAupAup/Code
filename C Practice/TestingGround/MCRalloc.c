#include <stdlib.h>
#include <stdio.h>

// -------------------------------------------------------------
// -------------------------------------------------------------

/*Task



Dynamic Allocated Array



*/

// -------------------------------------------------------------
// -------------------------------------------------------------
// F

// -------------------------------------------------------------
// -------------------------------------------------------------
// M

int main(void)
{

    int a;
    printf("input number of elements\n");
    scanf("%d", &a);
    printf("Submitted %d elements\n", a);

    int *A = malloc(a * sizeof(int)); // or calloc(a,sizeof(int));


    for (int i = 0; i < a; i++)
    {

        A[i] = i;
        printf("%d \n", A[i]);
    }

// All this is remained allocated untill free() !!!

    printf("\n");
}