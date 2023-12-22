
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct regs
{
    uint8_t pc; // Befehlszeiger
    uint8_t fa; // Flags + Akkumulator
    uint8_t ix; // Indexregister
};

int power(int basis, int exponent)
{
    switch (exponent)
    {
    case 0:
        return 1;
    case 1:
        return basis;
    default:
        return power(basis, exponent - 1) * basis;
    }
}

int retBit(uint8_t integer, int nthBit)
{
    int eins = 1 << nthBit;
    int check = (integer & eins);
    int res = check >> nthBit;
    return res;
}

void updatePC(struct regs *reg, uint8_t *cmd, int *indexCMD)
{
    if (*indexCMD >= 0 && *indexCMD < sizeof(cmd) / sizeof(uint8_t))
    {
        reg->pc = cmd[*indexCMD];
    }
    else
    {
        printf("Abbruch hier\n");
    }
};
int identifyDestinationAdr(int *_2_adrBitVector)
{
    int temp = 0;
    for (int i = 0; i <= 1; ++i)
    {

        if (_2_adrBitVector[i] == 1)
        {
            temp += power(2, i);
        }
    }
    return temp;
};

int retFullValue(int *bitVector)
{
    int res = 0;
    for (int i = 0; i <= 7; ++i)
    {
        if (bitVector[i] == 1)
        {
            res = res + power(2, i);
        }
    };
    return res;
};

int *fetch4BitAkku(struct regs *reg)
{
    int *temp = (int *)malloc(4 * sizeof(int));

    for (int i = 0; i <= 3; ++i)
    {
        temp[i] = retBit(reg->fa, i);
    }
    return temp;
};
int *fetch4BitIl(struct regs *reg)
{
    int *temp = (int *)malloc(4 * sizeof(int));

    for (int i = 0; i <= 3; ++i)
    {
        temp[i] = retBit(reg->ix, i);
    }
    return temp;
};
int *fetch4BitIh(struct regs *reg)
{
    int *temp = (int *)malloc(4 * sizeof(int));
    int c = 0;
    for (int i = 4; i <= 7; ++i)
    {
        temp[c] = retBit(reg->ix, i);
        ++c;
    }
    return temp;
};
int *fetch8BitData(struct regs *reg, uint8_t *data)
{
    printf("data %d\n",data[83]);
    int *temp = (int *)malloc(8 * sizeof(int));

    for (int i = 0; i <= 7; ++i)
    {
        temp[i] = retBit(data[(reg->ix/2)], i);
    }
    return temp;
};
int *fetch4BitData(struct regs *reg, uint8_t *data)
{
    int *temp = (int *)malloc(4 * sizeof(int));

    if ((reg->ix) % 2 == 0)
    {
        for (int i = 0; i <= 3; ++i)
        {
            temp[i] = retBit(data[(reg->ix / 2)], i);
        }
        return temp;
    }
    else
    {
        int j = 0;
        for (int i = 4; i <= 7; ++i)
        {
            temp[j] = retBit(data[(reg->ix / 2)], i);
            ++j;
        }
        return temp;
    }
}
void initializeWithZero(uint8_t *data)
{
    for (size_t i = 0; i < 127; i++)
    {
        data[i] = 0;
    }
};

int main()
{
    // 0-00--0-00-0-0-0-0-0-0-0-0-0--00--00-0-0-0-0--00-0--00-0-0--00-0-0-0--00-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-

    uint8_t cmd[256] = {[0] = 0b11010101, [1] = 0b00101010};
    struct regs a = {.fa = 0b10111010, .ix = 0b10100111, .pc = 0b10010110};
    struct regs *b = &a;
    uint8_t data[128];

       // printf("%d\n",data[83]);
    uint8_t data2[128];

    initializeWithZero(data);
    initializeWithZero(data2);
    data[a.ix/2] = 0b11111100;
    // 0-00--0-00-0-0-0-0-0-0-0-0-0--00--00-0-0-0-0--00-0--00-0-0--00-0-0-0--00-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-
    int *z = fetch4BitData(b,data);
    for (int i = 0; i <= 3; ++i){
        printf("-%d",z[i]);
    }
    printf("\n");
        // 0-00--0-00-0-0-0-0-0-0-0-0-0--00--00-0-0-0-0--00-0--00-0-0--00-0-0-0--00-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-

        /*
            int indexCMD = 1; // Testing updatepc
            printf("%d\n", b->pc);
            updatePC(b, cmd, &indexCMD);
            printf("%d\n", b->pc); // Testing updatepc
        */
        // 0-00--0-00-0-0-0-0-0-0-0-0-0--00--00-0-0-0-0--00-0--00-0-0--00-0-0-0--00-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-

        for (size_t i = 0; i <= 7; i++)
        {
            printf("%d", retBit(b->fa, i));
        }

    printf("\n");
    // 0-00--0-00-0-0-0-0-0-0-0-0-0--00--00-0-0-0-0--00-0--00-0-0--00-0-0-0--00-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-

    int j = 0;
    int _2_bitVectorAdr[2];
    for (int i = 4; i <= 5; ++i)
    {
        _2_bitVectorAdr[j] = retBit(b->pc, i);
        ++j;
    }
    int adrDestination = identifyDestinationAdr(_2_bitVectorAdr);
    printf(" current adr type is %d\n", adrDestination);

    // 0-00--0-00-0-0-0-0-0-0-0-0-0--00--00-0-0-0-0--00-0--00-0-0--00-0-0-0--00-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-

    int tempBitVector[8]; // testing cmd read

    int commandNr = -1;

    // [0] LSB [7] MSB
    for (int i = 0; i <= 7; ++i)
    {
        tempBitVector[i] = retBit(b->fa, i);
        printf("%d", tempBitVector[i]);
    };

    printf("\n");

    switch (tempBitVector[7]) // Check last (LSB) two bits for Command (00 = 0 / 11 = 1)
    {
    case 0:

        switch (tempBitVector[6])
        {
        case 0:
            commandNr = 0; // -> 00 = Command 0 = ldi
            printf("ldi\n");
            break;

        case 1:
            commandNr = -2; // Prefix for all 01---XXXX commands
            break;
        }
        break;

    case 1:
        switch (tempBitVector[6])
        {

        case 0:
            commandNr = -3; // Prefix for all 10---- commands
            break;

        case 1:
            commandNr = 1; // -> 11 = Command 1 = bcc
            printf("bcc\n");
            break;
        }
        break;
    }

    if (commandNr == -2) // 01--xxxx
    {
        switch (tempBitVector[5])
        {
        case 0: // 010-xxxx

            switch (tempBitVector[4])
            {
            case 0:
                commandNr = 2; // 0100 mv
                printf("mv\n");
                break;

            case 1:
                commandNr = 3; // 0101 jr
                printf("jr\n");
                break;
            }
            break;

        case 1: // 011-xxxx
            switch (tempBitVector[4])
            {
            case 0: // 0110
                // Unrecognised Command
                break;

            case 1: // 0111/1111 halt
                if (tempBitVector[3] == 1 && tempBitVector[2] == 1 && tempBitVector[1] == 1 && tempBitVector[0] == 1)
                {
                    commandNr = 4;
                    printf("halt\n");
                }
                else
                { // Unrecognised Command
                }
                break;
            }
            break;
        }
    }

    if (commandNr == -3) // 10-----
    {
        switch (tempBitVector[5]) // 10x
        {
        case 0: // 100....
            // Unrecognisd Command
            break;

        case 1: // 101x
            switch (tempBitVector[4])
            {
            case 0: // 1010xxxx
                commandNr = -4;
                break;

            case 1: // 1011xxxx
                commandNr = -5;
                break;
            }
            break;
        }
    }

    if (commandNr == -4) // 1010--xx
    {

        switch (tempBitVector[3])
        {
        case 0:
            switch (tempBitVector[2])
            {
            case 0:
                commandNr = 5; // 101000 add
                printf("add\n");
                break;

            case 1:
                commandNr = 6; // 101001 adc
                printf("adc\n");
                break;
            }
            break;

        case 1:
            switch (tempBitVector[2])
            {
            case 0:
                commandNr = 7; // 101010 and
                printf("and\n");
                break;

            case 1:
                commandNr = 8; // 101011 or
                printf("or\n");
                break;
            }
            break;
        }
    }

    if (commandNr == -5)
    {

        switch (tempBitVector[3])
        {
        case 0:
            switch (tempBitVector[2])
            {
            case 0:
                commandNr = 9; // 101100 xor
                printf("xor\n");
                break;
            case 1:
                commandNr = 10; // 101101 neg
                printf("neg\n");
                break;
            }
            break;

        case 1:
            if (tempBitVector[2] == 0)
            {
                commandNr = 11; // cpc 101110
                printf("cpc\n");
            }
            break;
        }
    }


int tmpea = 2;
int check = (1 << 2);
tmpea = tmpea ^ check;
printf("\n%d\n",tmpea);
};