#include <stdlib.h>
#include <stdio.h>

// -------------------------------------------------------------
// -------------------------------------------------------------

/*Task







*/

// -------------------------------------------------------------
// -------------------------------------------------------------
// F

// -------------------------------------------------------------
// -------------------------------------------------------------
// M

int main(void)
{
    void *p;

    int *x;

    int a = 4;

    x = &a;

    //void* malloc(size) // allocates size in bytes but does not initialize = trash values if allocated space is not initialized
    p = malloc(sizeof(int *) * 8);



    printf(" &x = %u , x = %u\n\n", &x, x); // On Stack
    printf("&p = %u , p = %u\n", &p, p); // p -> (line 35) first & of allocated space on the heap
                                            // to be able to use the allocated space on the heap, typecasting is required??
}                                               // only then *p = 2; (for intigers) is valid