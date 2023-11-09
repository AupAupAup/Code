#include <stdio.h>


int main(void)
{

    {
        int a = 42;
        {
            printf("%d\n", a);
        }
    }

    
{
    int a = 7;
    printf("%d\n", a);
}

}