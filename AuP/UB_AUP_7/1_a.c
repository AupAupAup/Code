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
    WRONG_NUMBER_OF_ARGUMENTS,
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
    unsigned int i = 0;
    for (char c = '\0'; c != input[i]; ++i)
        ;
    if ((i / x_dim == x_dim) && (i / y_dim == y_dim))
    {
        return true;
    }
    else
    {
        return false;
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
    case ('R'):
    {
        ++duck->position.x;
        if (duck->position.x > x_dim)
        {
            --duck->position.x;
            printf("invalid move\n");
        }
    }
    break;
    case ('L'):
    {
        --duck->position.x;
        if (duck->position.x < x_dim)
        {
            ++duck->position.x;
            printf("invalid move\n");
        }
        break;
    }
    case ('U'):
    {
        --duck->position.y;
        if (duck->position.y < y_dim)
        {
            ++duck->position.y;
            printf("invalid move\n");
        }
        break;
    }

    case ('D'):
    {
        ++duck->position.y;
        if (duck->position.y > y_dim)
        {
            --duck->position.y;
            printf("invalid move\n");
        }
    }
    default:
    {
        printf("Hello :)\n");
        break;
    }
    }
}

bool is_valid(char instr)
{
    switch (instr)
    {

    case 'D':

    case 'U':

    case 'L':

    case 'R':

        return true;
    default:
    {
        return false;
    }
    }
}

void eat(duck_t *duck, size_t x_dim, size_t y_dim, field_t game_board[x_dim][y_dim])
{
    if (game_board[duck->position.x][duck->position.y] == ('F'))
    {
        duck->hunger -= 1;
        game_board[duck->position.x][duck->position.y] = ('E');
    }
}

bool still_hungry(duck_t duck)
{

    if (duck.hunger == 0)
    {
        return false;
    }
    else
    {
        return true;
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

    size_t x_dim = atoi(argv[1]);
    size_t y_dim = atoi(argv[2]);

    duck_t duck;

    printf("[X] [Y] [HUNGERWERT]");

    scanf("%zu %zu %u", &duck.position.x, &duck.position.y, &duck.hunger);

    field_t game_board[x_dim][y_dim];

    fill_game_board(x_dim, y_dim, game_board, argv[3]);

    print_game_board(x_dim, y_dim, game_board);

    for (int i = 1; still_hungry(duck) == true; ++i)
    {
        printf("X:%lu Y:%lu\n", duck.position.x, duck.position.y);
        eat(&duck, x_dim, y_dim, game_board);
        char instr;
        printf("--- round %d ---\n\n", i);
        scanf("%c\n", &instr);
        while ((is_valid(instr) == false))
        {
            scanf("%c\n", &instr);
        }

        move(instr, &duck, x_dim, y_dim);
        eat(&duck, x_dim, y_dim, game_board);
        print_game_board(x_dim, y_dim, game_board);
    }

    printf("GG\n");
}