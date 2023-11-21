#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
    SUCCESS = 0,
    WRONG_NUMBER_OF_ARGUMENTS = 2,
    WRONG_INPUT_SIZE = 3,
    INVALID_MOVE = 4

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

    /* for (int n = 0; n < strlen(input); ++n)
    {
        if (input[n] != 'E')
        {
            return 0;
        }
    }*/

    unsigned int i = 0;
    for (char c = '\0'; c != input[i]; ++i)
        ;
    if ((i / x_dim == x_dim) && (i / y_dim == y_dim))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void fill_game_board(size_t x_dim, size_t y_dim, field_t game_board[x_dim][y_dim], const char *input)
{
    for (int j = 0; j < y_dim; ++j)
    {
        for (int i = 0; i < x_dim; ++i)
        {
            game_board[i][j] = *(input);
            input += 1;
        }
    }
}

void print_game_board(size_t x_dim, size_t y_dim, field_t game_board[x_dim][y_dim])
{
    for (int j = 0; j < y_dim; ++j)
    {
        for (int i = 0; i < x_dim; ++i)
        {
            printf("%c", game_board[i][j]);
        }
        printf("\n");
    }
}

error_t move(char instr, duck_t *duck, size_t x_dim, size_t y_dim)
{

    switch (instr)
    {
    case 'R':
        duck->position.x + 1;
        if (duck->position.x > x_dim)
        {
            duck->position.x - 1;
            printf("invalid move\n");
        }
        else
        {
            printf("Success\n");
        }

        break;

    case 'L':
        duck->position.x - 1;
        if (duck->position.x < x_dim)
        {
            duck->position.x + 1;
            printf("invalid move\n");
        }
        else
        {
            printf("Success\n");
        }
        break;

    case 'U':
        duck->position.y - 1;
        if (duck->position.y < y_dim)
        {
            duck->position.y + 1;
            printf("invalid move\n");
        }
        else
        {
            printf("Success\n");
        }
        break;

    case 'D':
        duck->position.y + 1;
        if (duck->position.y > y_dim)
        {
            duck->position.y - 1;
            printf("invalid move\n");
        }
        else
        {
            printf("Success\n");
        }
    default:
        break;
    }
}

bool is_valid(char instr)
{
    if (instr == 'U' || instr == 'D' || instr == 'L' || instr == 'R')
    {

        return 1;
    }
    else
    {
        return 0;
    }
}
void eat(duck_t *duck, size_t x_dim, size_t y_dim, field_t game_board[x_dim][y_dim])
{
    if (game_board[duck->position.x][duck->position.y] == 'F')
    {
        duck->hunger -= 1;
        game_board[duck->position.x][duck->position.y] == 'E';
    }
}


/*void print_first_ente(size_t x_dim, size_t y_dim, field_t game_board[x_dim][y_dim])
{
size_t x;
size_t y;
printf("Wo startet die ente [X][Y]\n");
scanf("%lu %lu",&x,&y);
game_board[x][y] = '@';
}
*/
// -------------------------------------------------------------
// -------------------------------------------------------------
// M

int main(int argc, char *argv[])
{

    if (check_input_size(atoi(argv[1]), atoi(argv[2]), argv[3]) == 0)
    {
        printf("error_t: \n");
        return 3;
    }

    duck_t duck;

    printf("[X] [Y] [HUNGERWERT]");

    scanf("%zu %zu %zu", duck.position.x, duck.position.y, duck.hunger); // huh


    field_t game_board[atoi(argv[1])][atoi(argv[2])];

    fill_game_board(atoi(argv[1]), atoi(argv[2]), game_board, argv[3]);

    print_game_board(atoi(argv[1]), atoi(argv[2]), game_board);

    while (duck.hunger != 0)
    {

        printf("Was soll die ente Machen? \n\nUP  = U\nDOWN = D\nLEFT = L\nRIGHT = R");
        char instr;
        scanf("%c", &instr);
        while (is_valid == 0)
        {

            printf("Falsche Eingabe\n\nWas soll die ente Machen? \n\nUP  = U\nDOWN = D\nLEFT = L\nRIGHT = R");
            scanf("%c", &instr);
        }

        move(instr, &duck, atoi(argv[1]), atoi(argv[2]));
    }

printf("GG\n");
}