
#include <stdio.h>
// -------------------------------------------------------------
// -------------------------------------------------------------

/*Task


Aufgaben: Schreiben Sie eine Quelltextdatei recursions.c, welche die folgenden Funktionen
rein rekursiv (ohne Verwendung von Schleifen) implementieren soll:
• Zählen von k bis 0
void countDown(unsigned int k);
• Zählen von 0 bis k
void countUp(unsigned int k)
• Zählen von k bis 0 und wieder bis k
void countDownUp(unsigned int k)




*/

// -------------------------------------------------------------
// -------------------------------------------------------------
// F

void countDown(unsigned int k)
{
    if (k == 0)
    {
        return;
    }
    printf("%u ", k);
    return countDown(k - 1);
}

void countUp(unsigned int k)
{
    if (k == 0)
    {
        return;
    }
    else
    {
        countUp(k - 1);
    }
    printf("%u ", k);
}

void countDownUp(unsigned int k)
{

    if (k == 0)
    {
        if (k == 0)
        {
            return;
        }
        else
        {
            countUp(k - 1);
        }
        printf("%u ", k);
    }
    printf("%u ", k);
    return countDown(k - 1);
}
// -------------------------------------------------------------
// -------------------------------------------------------------
//

void main(void)
{

    int k = 100;
    countDown(k);
}
