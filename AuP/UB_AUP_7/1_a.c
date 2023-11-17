#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
// -------------------------------------------------------------
// -------------------------------------------------------------

/*Task







*/

// -------------------------------------------------------------
// -------------------------------------------------------------
// F

typedef enum
{
    FOOD,
    EMPTY
} field_t;

typedef enum
{
    SUCCESS,
    WRONG_NUMBER_OF_ARGUMENTS,
    WRONG_INPUT_SIZE,
    INVALID_MOVE
} error_t;

typedef struct
{
    size_t x;
    size_t y;
} coord_t;

typedef struct
{
    coord_t position;
    int hunger;
} duck_t;

bool check_input_size(size_t x_dim, size_t y_dim, char const *input)
{
    unsigned int i = 0;
    for (char c = '\0'; c != input[i]; ++i)
        ;
    printf("%u\n", i);

    if ((i == x_dim) && (i == y_dim))
    {
        printf("Wat1\n");
        return true;
    }
    else
    {
        printf("Wat3\n");
        return false;
    }
}

/* Alternativ
    int i = 0;
    for (char c = '\0'; c != argv[3][i]; ++i)
        ;
    if (i != argv[1])
    {
        return -1;
    }
*/

// -------------------------------------------------------------
// -------------------------------------------------------------
// M

int main(int argc, char *argv[])
{
    if ((check_input_size(atoi(argv[1]), atoi(argv[2]), argv[3])) == false)
    {
        
    }
}