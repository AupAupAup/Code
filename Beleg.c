#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
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
int zweierkomplement(int value)
{
    for (int i = 0; i <= 3; ++i)
    {
        int eins = (1 << i);
        value = value ^ eins;
    }
    value += 1;

    if (retBit(value, 3) == 1)
    {
        value -= 8;
    }
    else
    {
        value *= -1;
    }
    return value;
};
void set0Bit(uint8_t *value, int nthBit)
{
    int eins = 1 << nthBit;
    *value = ((*value) ^ eins);
};
void set1Bit(uint8_t *value, int nthBit)
{
    int eins = 1 << nthBit;
    *value = ((*value) | eins);
};
void bitOverride(int adrCase, int value, struct regs *reg, uint8_t *data)
{
    if(adrCase == 0)
    {
        for (int i = 0, c = 0; i <= 3; ++i, ++c)
        {
            if (retBit(value, c) == 0)
            {
                if (retBit(reg->fa, i) == 1)
                {
                    set0Bit(&reg->fa, i);
                }
            }
            else if (retBit(value, c) == 1)
            {
                set1Bit(&reg->fa, i);
            }
        }
    }
    if(adrCase == 1){ // il
        for (int i = 0, c = 0; i <= 3; ++i, ++c)
        {
            if (retBit(value, c) == 0)
            {
                if (retBit(reg->ix, i) == 1)
                {
                    set0Bit(&reg->ix, i);
                }
            }
            else if (retBit(value, c) == 1)
            {
                set1Bit(&reg->ix, i);
            }
        }
    }
    if(adrCase == 2){
        for (int i = 4, c = 0; i <= 7; ++i, ++c)
        {
            if (retBit(value, c) == 0)
            {
                if (retBit(reg->ix, i) == 1)
                {
                    set0Bit(&reg->ix, i);
                }
            }
            else if (retBit(value, c) == 1)
            {
                set1Bit(&reg->ix, i);
            }
        }
    }
    if(adrCase == 3){ // ix / data
        int i = 0;
        if ((reg->ix) % 2 == 1)
        {
            i += 4;
        }
        int index = (reg->ix / 2);
        int temp = i + 3;
        int c = 0;
        for (; i <= temp; ++i, ++c)
        {
            if (retBit(value, c) == 0)
            {
                if (retBit(data[index], i) == 1)
                {
                    set0Bit(&(data[index]), i);
                }
            }
            else if (retBit(value, c) == 1)
            {
                set1Bit(&(data[index]), i);
            }
        }
    }
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
int *fetch8BitAkku(struct regs *reg)
{
    int *temp = (int *)malloc(8 * sizeof(int));

    for (int i = 0; i <= 7; ++i)
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
int *fetch4BitCMD(uint8_t *cmd, int *indexCMD)
{
    int *temp = (int *)malloc(4 * sizeof(int));

    for (int i = 0; i <= 3; ++i)
    {
        temp[i] = retBit(cmd[(*indexCMD)], i);
    }
    return temp;
}
int *fetch8BitCMD(uint8_t *cmd, int *indexCMD)
{
    int *temp = (int *)malloc(8 * sizeof(int));

    for (int i = 0; i <= 7; ++i)
    {
        temp[i] = retBit(cmd[(*indexCMD)], i);
    }
    return temp;
}
int retCellValue(int *bitVector)
{
    int res = 0;
    for (int i = 0; i <= 3; ++i)
    {
        if (bitVector[i] == 1)
        {
            res = res + power(2, i);
        }
    };
    return res;
};
int ret8bCellValue(int *bitVector)
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
int *retAllBitsMALLOC(uint8_t *data, int currentIndex)
{
    int *bitVector = (int *)malloc(8 * sizeof(int));
    for (int i = 0; i <= 7; ++i)
    {
        bitVector[i] = retBit(data[currentIndex], i);
    }
    return bitVector;
}
int *retLsbBitsMALLOC(int *modifiedBitVector) //
{

    int *bitVector = (int *)malloc(4 * sizeof(int));

    for (int i = 0; i <= 3; ++i)
    {
        bitVector[i] = modifiedBitVector[i];
    }
    return bitVector;
};
int *retMsbBitsMALLOC(int *modifiedBitVector) //
{

    int *bitVector = (int *)malloc(4 * sizeof(int));

    int count = 0;
    for (int i = 4; i <= 7; ++i)
    {
        bitVector[count] = modifiedBitVector[i];
        ++count;
    }
    return bitVector;
};
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
    return check;
};
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
            check = 1;
            return check;
        }
    }
    return check;
};
char singleIntToChar(int integer)
{

    switch (integer)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    default:
        return '-';
        break;
    }
}
void assembleStringPutIntoHeap(int indexInteger, int *partBitVector, char *callocStringArray)
{
    int strlength = strlen(callocStringArray);
    int temp = 0;
    for (int i = 1 + strlength; i >= 0 + strlength; --i)
    {
        temp = indexInteger % 16;
        callocStringArray[i] = singleIntToChar(temp);
        indexInteger /= 16;
    }

    callocStringArray[2 + strlength] = ' ';

    int tempCellValue = retCellValue(partBitVector);

    callocStringArray[3 + strlength] = singleIntToChar(tempCellValue);
    callocStringArray[4 + strlength] = '\n';
};
char *retChanges(uint8_t *dataOriginal, uint8_t *dataModified)
{
    int saveCalledChanges = 0;
    char *toRetArray = (char *)calloc(5 * 255 + 1, sizeof(char));

    for (int i = 0; i <= 127; ++i)
    {
        int *originalBitVector = retAllBitsMALLOC(dataOriginal, i);
        int *modifiedBitVector = retAllBitsMALLOC(dataModified, i);
        int is_lsb = funcToCheckLsbPart(originalBitVector, modifiedBitVector); // is one when lsb part is changed
        int is_msb = funcToCheckMsbPart(originalBitVector, modifiedBitVector); // is two when msb part is changed
        if (is_lsb == 1)
        {
            int cellIndexLsb = (2 * i);
            int *lsbBitVector = retLsbBitsMALLOC(modifiedBitVector);
            assembleStringPutIntoHeap(cellIndexLsb, lsbBitVector, toRetArray);
            saveCalledChanges += 1;
            free(lsbBitVector);
        }

        if (is_msb == 1)
        {
            int cellIndexMsb = ((2 * i) + 1);
            int *msbBitVector = retMsbBitsMALLOC(modifiedBitVector);
            assembleStringPutIntoHeap(cellIndexMsb, msbBitVector, toRetArray);
            saveCalledChanges += 1;
            free(msbBitVector);
        }

        free(originalBitVector);
        free(modifiedBitVector);
    }

    if (saveCalledChanges > 0)
    {
        int temp = strlen(toRetArray);
        toRetArray[temp + 1] = '\0';
        return toRetArray;
    }
    else
    {
        int temp = strlen(toRetArray);
        toRetArray[temp] = '\0';
        return toRetArray;
    }
};
int readCommand(struct regs *reg, int *indexCMD, uint8_t *cmd)
{
    int commandNr = -1;
    int *tempBitVector = fetch8BitCMD(cmd, indexCMD);
    if (ret8bCellValue(tempBitVector) > 255)
    {
        
        return -400;
    }

    if (tempBitVector[7] == 0 && tempBitVector[6] == 0)
    {
        commandNr = 0;
    } // ldi
    if (tempBitVector[7] == 1 && tempBitVector[6] == 1)
    {
        commandNr = 1;
    } // bcc
    if (tempBitVector[7] == 0 && tempBitVector[6] == 1 && tempBitVector[5] == 0 && tempBitVector[4] == 0)
    {
        commandNr = 2;
    } // mv
    if (tempBitVector[7] == 0 && tempBitVector[6] == 1 && tempBitVector[5] == 0 && tempBitVector[4] == 1)
    {
        commandNr = 3;
    } // jr
    if (tempBitVector[7] == 1 && tempBitVector[6] == 0 && tempBitVector[5] == 1 && tempBitVector[4] == 0 && tempBitVector[3] == 0 && tempBitVector[2] == 0)
    {
        commandNr = 5;
    } // add
    if (tempBitVector[7] == 1 && tempBitVector[6] == 0 && tempBitVector[5] == 1 && tempBitVector[4] == 0 && tempBitVector[3] == 0 && tempBitVector[2] == 1)
    {
        commandNr = 6;
    } // adc
    if (tempBitVector[7] == 1 && tempBitVector[6] == 0 && tempBitVector[5] == 1 && tempBitVector[4] == 0 && tempBitVector[3] == 1 && tempBitVector[2] == 0)
    {
        commandNr = 7;
    } // and
    if (tempBitVector[7] == 1 && tempBitVector[6] == 0 && tempBitVector[5] == 1 && tempBitVector[4] == 0 && tempBitVector[3] == 1 && tempBitVector[2] == 1)
    {
        commandNr = 8;
    } // or
    if (tempBitVector[7] == 1 && tempBitVector[6] == 0 && tempBitVector[5] == 1 && tempBitVector[4] == 1 && tempBitVector[3] == 0 && tempBitVector[2] == 0)
    {
        commandNr = 9;
    } // xor
    if (tempBitVector[7] == 1 && tempBitVector[6] == 0 && tempBitVector[5] == 1 && tempBitVector[4] == 1 && tempBitVector[3] == 0 && tempBitVector[2] == 1)
    {
        commandNr = 10;
    } // neg
    if (tempBitVector[7] == 1 && tempBitVector[6] == 0 && tempBitVector[5] == 1 && tempBitVector[4] == 1 && tempBitVector[3] == 1 && tempBitVector[2] == 0)
    {
        commandNr = 11;
    } // cpl
    if (tempBitVector[7] == 0 && tempBitVector[6] == 1 && tempBitVector[5] == 1 && tempBitVector[4] == 1 && tempBitVector[3] == 1 && tempBitVector[2] == 1 && tempBitVector[1] == 1 && tempBitVector[0] == 1)
    {
        commandNr = 4;
    } // halt
    free(tempBitVector);
    return commandNr;
};
void ldi(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *_4BitCMD = fetch4BitCMD(cmd, indexCMD);
    int *_8BitCMD = fetch8BitCMD(cmd, indexCMD);
    int Value_4BitCMD = retCellValue(_4BitCMD);

    if (_8BitCMD[5] == 0 && _8BitCMD[4] == 0)
    {
        bitOverride(0, Value_4BitCMD, reg, data);
    }
    if (_8BitCMD[5] == 0 && _8BitCMD[4] == 1)
    {
        bitOverride(1, Value_4BitCMD, reg, data);
    }
    if (_8BitCMD[5] == 1 && _8BitCMD[4] == 0)
    {
        bitOverride(2, Value_4BitCMD, reg, data);
    }
    if (_8BitCMD[5] == 1 && _8BitCMD[4] == 1)
    {
        bitOverride(3, Value_4BitCMD, reg, data);
    }
    free(_4BitCMD);
    free(_8BitCMD);
};
void mv(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch8BitCMD(cmd, indexCMD);
    if (adresses[1] == 0 && adresses[0] == 0)
    {
        if (adresses[3] == 0 && adresses[2] == 1)
        {
            int *temp = fetch4BitAkku(reg);
            int value = retCellValue(temp);   // value von a
            bitOverride(1, value, reg, data); // nach il
            free(temp);
        };
        if (adresses[3] == 1 && adresses[2] == 0)
        {
            int *temp = fetch4BitAkku(reg);
            int value = retCellValue(temp);   // value von a
            bitOverride(2, value, reg, data); // nach ih
            free(temp);
        }
        if (adresses[3] == 1 && adresses[2] == 1)
        {
            int *temp = fetch4BitAkku(reg);
            int value = retCellValue(temp);   // value von a);
            bitOverride(3, value, reg, data); // nach data[ix/2]
            free(temp);
        }
    };
    if (adresses[1] == 0 && adresses[0] == 1)
    {
        if (adresses[3] == 0 && adresses[2] == 0)
        {
            int *temp = fetch4BitIl(reg);
            int value = retCellValue(temp);   // value von li
            bitOverride(0, value, reg, data); // nach a
            free(temp);
        };
        if (adresses[3] == 1 && adresses[2] == 0)
        {
            int *temp = fetch4BitIl(reg);
            int value = retCellValue(temp);   // value li
            bitOverride(2, value, reg, data); // nach ih
            free(temp);
        }
        if (adresses[3] == 1 && adresses[2] == 1)
        {
            int *temp = fetch4BitIl(reg);
            int value = retCellValue(temp);   // value von li;
            bitOverride(3, value, reg, data); // nach data[ix/2]
            free(temp);
        }
    }
    if (adresses[1] == 1 && adresses[0] == 0)
    {
        if (adresses[3] == 0 && adresses[2] == 0)
        {
            int *temp = fetch4BitIh(reg);
            int value = retCellValue(temp);   // value von li
            bitOverride(0, value, reg, data); // nach a
            free(temp);
        };
        if (adresses[3] == 0 && adresses[2] == 1)
        {
            int *temp = fetch4BitIh(reg);
            int value = retCellValue(temp);   // value li
            bitOverride(1, value, reg, data); // nach ih
            free(temp);
        }
        if (adresses[3] == 1 && adresses[2] == 1)
        {
            int *temp = fetch4BitIh(reg);
            int value = retCellValue(temp);   // value von li;
            bitOverride(3, value, reg, data); // nach data[ix/2]
            free(temp);
        }
    };
    if (adresses[1] == 1 && adresses[1] == 1)
    {
        if (adresses[3] == 0 && adresses[2] == 0)
        {
            int *temp = fetch4BitData(reg, data);
            int value = retCellValue(temp);   // value von li
            bitOverride(0, value, reg, data); // nach a
            free(temp);
        };
        if (adresses[3] == 0 && adresses[2] == 1)
        {
            int *temp = fetch4BitData(reg, data);
            int value = retCellValue(temp);   // value li
            bitOverride(1, value, reg, data); // nach ih
            free(temp);
        }
        if (adresses[3] == 1 && adresses[2] == 0)
        {
            int *temp = fetch4BitData(reg, data);
            int value = retCellValue(temp);   // value von li;
            bitOverride(2, value, reg, data); // nach data[ix/2]
            free(temp);
        }
    };
    free(adresses);
};
void jr(struct regs *reg, uint8_t *cmd, int *indexCMD)
{
    int *fetchedPc = fetch4BitCMD(cmd, indexCMD);
    int value = retCellValue(fetchedPc);
    value = zweierkomplement(value);
    *indexCMD += (value);
    if (value == 0)
    {
        *indexCMD += 1;
    }
    free(fetchedPc);
};
void bcc(struct regs *reg, uint8_t *cmd, int *indexCMD)
{
    int *fetchedPc = fetch8BitCMD(cmd, indexCMD);
    int *fetchedPc4 = fetch4BitCMD(cmd, indexCMD);
    int *fetchedFa = fetch8BitAkku(reg);
    if (fetchedFa[7] == fetchedPc[5] && fetchedFa[6] == fetchedPc[5])
    {
        int value = retCellValue(fetchedPc4);
        value = zweierkomplement(value);
        *indexCMD += (value);
        if (value == 0)
        {
            *indexCMD += 1;
        }
    };
    free(fetchedPc4);
    free(fetchedFa);
    free(fetchedPc);
};
void add(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch4BitCMD(cmd, indexCMD);
    int cFlag = 0;

    if (adresses[1] == 0 && adresses[0] == 0) // a
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int aValue = 2 * (retCellValue(a_4_Bit));
        if (aValue > 15)
        {

            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(a_4_Bit);
    }
    if (adresses[1] == 0 && adresses[0] == 1) // il
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *il_4_Bit = fetch4BitIl(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(il_4_Bit));
        aValue += ilValue;
        if (aValue > 15)
        {
            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(il_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 0) // ih
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *ih_4_Bit = fetch4BitIh(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(ih_4_Bit));
        aValue += ilValue;
        if (aValue > 15)
        {
            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ih_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 1) // ix / data
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *data_4_Bit = fetch4BitData(reg, data);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(data_4_Bit));
        aValue += ilValue;
        if (aValue > 15)
        {
            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(data_4_Bit);
        free(a_4_Bit);
    }
    free(adresses);
};
void adc(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch4BitCMD(cmd, indexCMD);
    int cFlag = 0;

    if (adresses[1] == 0 && adresses[0] == 0) // a
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int aValue = 2 * (retCellValue(a_4_Bit));
        if (retBit(reg->fa, 7) == 1 && retBit(reg->fa, 6) == 1)
        {
            aValue += 1;
            reg->fa = reg->fa ^ (1 << 7);
        }
        if (aValue > 15)
        {
            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(a_4_Bit);
    }
    if (adresses[1] == 0 && adresses[0] == 1) // il
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *il_4_Bit = fetch4BitIl(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(il_4_Bit));
        aValue += ilValue;
        if (retBit(reg->fa, 7) == 1 && retBit(reg->fa, 6) == 1)
        {
            aValue += 1;
            reg->fa = reg->fa ^ (1 << 7);
        }
        if (aValue > 15)
        {
            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(il_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 0) // ih
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *ih_4_Bit = fetch4BitIh(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(ih_4_Bit));
        aValue += ilValue;
        if (retBit(reg->fa, 7) == 1 && retBit(reg->fa, 6) == 1)
        {
            aValue += 1;
            reg->fa = reg->fa ^ (1 << 7);
        }
        if (aValue > 15)
        {
            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ih_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 1) // ix / data
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *data_4_Bit = fetch4BitData(reg, data);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(data_4_Bit));
        aValue += ilValue;
        if (retBit(reg->fa, 7) == 1 && retBit(reg->fa, 6) == 1)
        {
            aValue += 1;
            reg->fa = reg->fa ^ (1 << 7);
        }
        if (aValue > 15)
        {
            cFlag = 1;
            while (aValue > 15)
            {
                aValue = aValue - 16;
            }
        };
        bitOverride(0, aValue, reg, data);
        if (cFlag == 1)
        {
            reg->fa = reg->fa | (1 << 6);
        }
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(data_4_Bit);
        free(a_4_Bit);
    }
    free(adresses);
};
void andd(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch4BitCMD(cmd, indexCMD);
    if (adresses[1] == 0 && adresses[0] == 0) // a
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int aValue = (retCellValue(a_4_Bit)) & (retCellValue(a_4_Bit));

        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(a_4_Bit);
    }
    if (adresses[1] == 0 && adresses[0] == 1) // il
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *il_4_Bit = fetch4BitIl(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(il_4_Bit));
        aValue &= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(il_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 0) // ih
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *ih_4_Bit = fetch4BitIh(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(ih_4_Bit));
        aValue &= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ih_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 1) // ix / data
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *data_4_Bit = fetch4BitData(reg, data);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(data_4_Bit));
        aValue &= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(data_4_Bit);
        free(a_4_Bit);
    }
    free(adresses);
};
void orr(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch4BitCMD(cmd, indexCMD);
    if (adresses[1] == 0 && adresses[0] == 0) // a
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int aValue = (retCellValue(a_4_Bit)) | (retCellValue(a_4_Bit));

        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(a_4_Bit);
    }
    if (adresses[1] == 0 && adresses[0] == 1) // il
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *il_4_Bit = fetch4BitIl(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(il_4_Bit));
        aValue |= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(il_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 0) // ih
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *ih_4_Bit = fetch4BitIh(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(ih_4_Bit));
        aValue |= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ih_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 1) // ix / data
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *data_4_Bit = fetch4BitData(reg, data);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(data_4_Bit));
        aValue |= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(data_4_Bit);
        free(a_4_Bit);
    }
    free(adresses);
};
void xorr(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch4BitCMD(cmd, indexCMD);
    if (adresses[1] == 0 && adresses[0] == 0) // a
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int aValue = (retCellValue(a_4_Bit)) ^ (retCellValue(a_4_Bit));

        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(a_4_Bit);
    }
    if (adresses[1] == 0 && adresses[0] == 1) // il
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *il_4_Bit = fetch4BitIl(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(il_4_Bit));
        aValue ^= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(il_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 0) // ih
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *ih_4_Bit = fetch4BitIh(reg);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(ih_4_Bit));
        aValue ^= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ih_4_Bit);
        free(a_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 1) // ix / data
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int *data_4_Bit = fetch4BitData(reg, data);
        int aValue = (retCellValue(a_4_Bit));
        int ilValue = (retCellValue(data_4_Bit));
        aValue ^= ilValue;
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(data_4_Bit);
        free(a_4_Bit);
    }
    free(adresses);
};
void neg(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch4BitCMD(cmd, indexCMD);
    if (adresses[1] == 0 && adresses[0] == 0) // a
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int aValue = (retCellValue(a_4_Bit));
        for (int i = 0; i <= 3; ++i)
        {
            aValue ^= (1 << i);
        }
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(a_4_Bit);
    }
    if (adresses[1] == 0 && adresses[0] == 1) // il
    {
        int *il_4_Bit = fetch4BitIl(reg);
        int ilValue = (retCellValue(il_4_Bit));
        for (int i = 0; i <= 3; ++i)
        {
            ilValue ^= (1 << i);
        }
        bitOverride(1, ilValue, reg, data);
        if (ilValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(il_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 0) // ih
    {
        int *ih_4_Bit = fetch4BitIh(reg);
        int ihValue = (retCellValue(ih_4_Bit));
        for (int i = 0; i <= 3; ++i)
        {
            ihValue ^= (1 << i);
        }
        bitOverride(2, ihValue, reg, data);
        if (ihValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ih_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 1) // ix / data
    {
        int *ix_4_Bit = fetch4BitData(reg, data);
        int dataValue = (retCellValue(ix_4_Bit));
        for (int i = 0; i <= 3; ++i)
        {
            dataValue ^= (1 << i);
        }
        bitOverride(3, dataValue, reg, data);
        if (dataValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ix_4_Bit);
    }
    free(adresses);
};
void cpl(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD)
{
    int *adresses = fetch4BitCMD(cmd, indexCMD);
    if (adresses[1] == 0 && adresses[0] == 0) // a
    {
        int *a_4_Bit = fetch4BitAkku(reg);
        int aValue = (retCellValue(a_4_Bit));
        aValue = zweierkomplement(aValue);
        bitOverride(0, aValue, reg, data);
        if (aValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(a_4_Bit);
    }
    if (adresses[1] == 0 && adresses[0] == 1) // il
    {
        int *il_4_Bit = fetch4BitIl(reg);
        int ilValue = (retCellValue(il_4_Bit));
        ilValue = zweierkomplement(ilValue);
        bitOverride(1, ilValue, reg, data);
        if (ilValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(il_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 0) // ih
    {
        int *ih_4_Bit = fetch4BitIh(reg);
        int ihValue = (retCellValue(ih_4_Bit));
        ihValue = zweierkomplement(ihValue);
        bitOverride(2, ihValue, reg, data);
        if (ihValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ih_4_Bit);
    }
    if (adresses[1] == 1 && adresses[0] == 1) // ix / data
    {
        int *ix_4_Bit = fetch4BitData(reg, data);
        int dataValue = (retCellValue(ix_4_Bit));
        dataValue = zweierkomplement(dataValue);
        bitOverride(3, dataValue, reg, data);
        if (dataValue == 0)
        {
            reg->fa = reg->fa | (1 << 7);
        }
        else if (retBit(reg->fa, 7) == 1)
        {
            reg->fa = reg->fa ^ (1 << 7);
        }
        free(ix_4_Bit);
    }
    free(adresses);
};
void commandCenter(struct regs *reg, uint8_t *data, uint8_t *cmd, int *indexCMD, int commandNr /* ,, Possibly Change of State-> see halt*/)
{
    switch (commandNr)
    {
    case 0: // 00
        ldi(reg, data, cmd, indexCMD);
        break;
    case 1: // 11
        bcc(reg, cmd, indexCMD);
        break;
    case 2: // 01/00
        mv(reg, data, cmd, indexCMD);
        break;
    case 3: // 01/01
        jr(reg, cmd, indexCMD);
        break;
    case 4: // 0111/1111
        break;
    case 5: // 1010/00
        add(reg, data, cmd, indexCMD);
        break;
    case 6: // 1010/01
        adc(reg, data, cmd, indexCMD);
        break;
    case 7: // 1010/10
        andd(reg, data, cmd, indexCMD);
        break;
    case 8: // 1010/11
        orr(reg, data, cmd, indexCMD);
        break;
    case 9: // 1011/00
        xorr(reg, data, cmd, indexCMD);
        break;
    case 10: // 1011/01
        neg(reg, data, cmd, indexCMD);
        break;
    case 11: // 1011/10
        cpl(reg, data, cmd, indexCMD);
        break;
    default:
        break;
    }
}
char *simcpu(struct regs *registers, uint8_t data[128], uint8_t cmd[256])
{
    int readIndex = 0;
    int cmdsCounter = 0;
    uint8_t dataCopyBefore[128];
    for (int i = 0; i <= 127; ++i)
    {
        dataCopyBefore[i] = data[i];
    }
    while (cmdsCounter < 100)
    {
        int cmdNr = readCommand(registers, &readIndex, cmd);
        readIndex += 1;
        int commandIndex = readIndex - 1;
        if (cmdNr == -400 || cmdNr == 4)
        {
            char *res = retChanges(dataCopyBefore, data);
            return res;
        }
        commandCenter(registers, data, cmd, &commandIndex, cmdNr);
        ++cmdsCounter;
    }
    char *res = retChanges(dataCopyBefore, data);
    return res;
};



void initializeWithZero(uint8_t *data)
{
    for (size_t i = 0; i < 127; i++)
    {
        data[i] = 0;
    }
}

// -------------------------------------------------------------
// -------------------------------------------------------------
void main(void)
{
    uint8_t data[128];
    uint8_t data2[128];
    initializeWithZero(data);
    initializeWithZero(data2);
    uint8_t cmd[256] = {
        [0] = 0x0f, // ldi a, 15 => a hat den Wert 15 bzw. -1
        [1] = 0x48, // mv ih, a => ix enthält den Wert 240
        [2] = 0x44, // mv il, a => ix hat den Wert 255 ;
        [3] = 0x32, // ldi (ix), 2 => Adresse FF hat den Wert 2
        [4] = 0xa2, // add ih => a hat den Wert 14 bzw. -2
        [5] = 0x44, // mv il, a => ix hat den Wert 254
        [6] = 0x3a, // ldi (ix), 10 => Adresse FE hat den Wert A
        [7] = 0x7f, // halt => in data[127] steht 42 (bzw. 0x2a)
    };
    struct regs a = {.fa = 0, .ix = 0, .pc = 0};
    char *res = simcpu(&a, data, cmd);
    printf("%s",res);
    printf("-----------------STATS BELOW-------------------\n");
    // printf("%s\n", res);

}