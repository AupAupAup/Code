#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int antwort;
    int x = 2;
    
    antwort = x * (x + 1) * 7;
    printf("Die Antwort lautet %d\n", antwort);
    
    return antwort;
}