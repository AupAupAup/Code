#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

struct regs
{
    uint8_t pc; // Befehlszeiger
    uint8_t fa; // Flags + Akkumulator
    uint8_t ix; // Indexregister
};

// -------------------------------------------------------------
// -------------------------------------------------------------

// -------------------------------------------------------------
// -------------------------------------------------------------

char *simcpu(struct regs *registers, uint8_t data[128], uint8_t cmd[256]){

};

// -------------------------------------------------------------
//              PRINT DATA FUNCTION
// -------------------------------------------------------------
int retBit(uint8_t integer, int nthBit)
{
    int eins = 1 << nthBit;
    int check = (integer & eins);
    int res = check >> nthBit;
    return res;
}

void printData(uint8_t *data)
{

    for (int i = 0; i <= 127; ++i)
    {
        printf("INDEX %d \t", i);
        for (int v = 7; v >= 4; --v)
        {
            printf("%d", retBit(data[i], v));
        }
        printf("\t|\t");

        for (int j = 3; j >= 0; --j)
        {
            printf("%d", retBit(data[i], j));
        }
        printf("\t\n");
    }
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

// -------------------------------------------------------------
//               FIND AND RETURN CHANGES
// -------------------------------------------------------------

int countNumOfExecution(uint8_t integer)
{
    int k = 0;
    for (k; integer != 0; ++k)
    {
        integer = integer / 2;
    }
    return k;
}

//!!//!!//!!//!!//!!//!!
// MALLOC CLEARED ??????? []
// is msb downto lsb

/*int retBit(uint8_t integer, int nthBit)
{
    int eins = 1 << nthBit;
    int check = (integer & eins);
    int res = check >> nthBit;
    return res;
}*/

// *retAllBits => return all bits in int array
// returns pointer to integer array with the bitvalues of data[currentIndex]
// reminder lsb upto msb in bitvector => (dec) 2 = (b) 01000000
// for readability reversed output needed

int *retAllBits(uint8_t *data, int currentIndex)
{
    int *bitVector = (int *)malloc(8 * sizeof(int));
    for (int i = 0; i <= 7; ++i)
    {
        bitVector[i] = retBit(data[currentIndex], i);
    }
    return bitVector;
}

unsigned int funcToCheckLsbPart(int *original, int *modified)
{
    unsigned int check = 0;
    for (unsigned int i = 0; i <= 3; ++i)
    {
        if (original[i] == modified[i])
        {
            continue;
        }
        else
        {
            check = 1;
            return check;
        }
    }
}

unsigned int funcToCheckMsbPart(int *original, int *modified)
{
    unsigned int check = 0;
    for (unsigned int i = 4; i <= 7; ++i)
    {
        if (original[i] == modified[i])
        {
            continue;
        }
        else
        {
            check = 2;
            return check;
        }
    }
}

char *lsbFromHexAddressToString(int index, uint8_t *dataModified){};

char *retChanges(uint8_t *dataOriginal, uint8_t *dataModified)
{

    char *toRetArray = (char *)calloc(128, sizeof(uint8_t)); // don't Free => Ausgabe // hier will ich dann die kagga ablegen und zurueckgeben // countfalseexec muss evtl ptr sein
    int countFalseExecutions = 0;
    for (int i = 0; i <= 127; ++i)
    {

        int *original = retAllBits(dataOriginal, i); // wir machen bitvektoren aus den daten aus original und mod und wollen die dann mit beiden lsb und msb fnk vergleichen ob was changed ist
        int *modified = retAllBits(dataModified, i);

        int lsb = funcToCheckLsbPart(original, modified); // is one when lsb part is changed
        int msb = funcToCheckMsbPart(original, modified); // is two when msb part is changed

        free(original);
        free(modified);
    }

    free(toRetArray); // dont forget to remove this for returning the actual end
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void initializeWithZero(uint8_t *data)
{
    for (size_t i = 0; i < 127; i++)
    {
        data[i] = 0;
    }
}

// -------------------------------------------------------------
// -------------------------------------------------------------
int main(void)
{
    uint8_t data[128];
    uint8_t data2[128];
    initializeWithZero(data);
    initializeWithZero(data2);
    data2[2] = 0b10010000;
    
    int *original = retAllBits(data, 2);
    int *modified = retAllBits(data2, 2);

    int lsb = funcToCheckLsbPart(original, modified); // is one when lsb part is changed
    int msb = funcToCheckMsbPart(original, modified); // is two when msb part is changed

    if(lsb == 1){printf("lsb\n");};
    if(msb == 2){printf("msb\n");};

    uint8_t cmd[256] = {
        [0] = 0x0f, // ldi a, 15 => a hat den Wert 15 bzw. -1
        [1] = 0x48, // mv ih, a => ix enthält den Wert 240
        [2] = 0x44, // mv il, a => ix hat den Wert 255
        [3] = 0x32, // ldi (ix), 2 => Adresse FF hat den Wert 2
        [4] = 0xa2, // add ih => a hat den Wert 14 bzw. -2
        [5] = 0x44, // mv il, a => ix hat den Wert 254
        [6] = 0x3a, // ldi (ix), 10 => Adresse FE hat den Wert A
        [7] = 0x7f, // halt => in data[127] steht 42 (bzw. 0x2a)
    };
    // printData(data);

    int a = 0x42;
    int b = 72;
    int c = 0b1001000;

    // output in correct way is required(reversed) test

    int *testzweck = retAllBits(data2, 2);
    for (int i = 7; i >= 0; --i)
    {

        printf("%d", testzweck[i]);
    }
}




/* TODO


Return Function - > Check index (127) goes 0 - 127, data cell indexes -> 0 - 255 (right even, left uneven) - > turn into hex array and add this to an hex value array and return it to the calloc




*/