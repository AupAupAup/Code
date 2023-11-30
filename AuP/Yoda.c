#include <stdlib.h>
#include <stdio.h>

int charachtercounter(const char *sentence)
{
    if (*sentence == '\0')
    {
        return 1;
    }
    else
    {
        return charachtercounter(sentence + 1) + 1;
    }
}

int LocateIndexOfFirstCharacterOfLastWord(const char *sentence, int size)
{
    if (sentence[size] == ' ')
    {
        return size + 1;
    }
    else
    {
        return LocateIndexOfFirstCharacterOfLastWord(sentence, size - 1);
    }
}

void firstWordIntoNewArray(const char *sentence, char *ptcR, int indexLWFC, int check)
{

    if (sentence[indexLWFC] == '.' || sentence[indexLWFC] == '!')
    {
        return;
    }
    if (indexLWFC == check && sentence[indexLWFC] > 97) // for lowercase Make Big
    {
        *ptcR = sentence[indexLWFC] - 32;
        return firstWordIntoNewArray(sentence, ptcR + 1, indexLWFC + 1, check);
    }
    else // Uppercase
    {
        *ptcR = sentence[indexLWFC];
        return firstWordIntoNewArray(sentence, ptcR + 1, indexLWFC + 1, check);
    }

    *ptcR = sentence[indexLWFC];
    return firstWordIntoNewArray(sentence, ptcR + 1, indexLWFC + 1, check);
}

int whereDidILeft(char *ptcR)
{
    if (*ptcR == 0)
    {
        return 0;
    }

    return whereDidILeft(ptcR + 1) + 1;
}

void yeetTheRestInNew(const char *sentence, char *ptcR, int indexLWFC, int whereWasIAgain, int anothercheck)
{
    if (whereWasIAgain == anothercheck)
    {
        ptcR[whereWasIAgain] = sentence[0] + 32;
        return yeetTheRestInNew(sentence + 1, ptcR, indexLWFC, whereWasIAgain + 1, anothercheck);
    }

    if (whereWasIAgain - anothercheck == indexLWFC)
    {
        return;
    }

    ptcR[whereWasIAgain] = *sentence;
    return yeetTheRestInNew(sentence + 1, ptcR, indexLWFC, whereWasIAgain + 1, anothercheck);d
}
char *yoda(const char *const sentence)
{
    int size = charachtercounter(sentence);
    char *ptcR = (char *)malloc(size * sizeof(char));
    if (ptcR != NULL){
    int indexLWFC = LocateIndexOfFirstCharacterOfLastWord(sentence, size);
    int check = LocateIndexOfFirstCharacterOfLastWord(sentence, size);
    firstWordIntoNewArray(sentence, ptcR, indexLWFC, check);
    int whereWasIAgain = whereDidILeft(ptcR);
    int anothercheck = whereDidILeft(ptcR);
    ptcR[whereWasIAgain] = ' ';
    ++anothercheck;
    ++whereWasIAgain;
    indexLWFC -= 1;
    yeetTheRestInNew(sentence, ptcR, indexLWFC, whereWasIAgain, anothercheck);
    ptcR[size - 2] = sentence[size - 2];
    ptcR[size - 1] = '\0';
    return ptcR;}
}

///////////////////

int main()
{
    ///////////////////////////////////
    char *sentence = "Die macht ist Stark!"; // 21 Chars (0 included)
    printf("1 = %s\n", sentence);
    char * res = yoda(sentence);
    printf("2 ==%s\n\n",res);
    free(res);
    /*
     

    ///////////////////////////////////
        char *sentence = "Der Affe ist cool.";                                                           // given string
        printf("Out Given String = %s\n", sentence);                                                     //print it

        int size = charachtercounter(sentence);                                                          // count how many character the given string has '0' included
        char *ptcR = malloc(size);                                                                       // allocate space corresponding to the count of characters
        // printf("The size of size = %d\n",size);                                                       // (debug)

        int indexLWFC = LocateIndexOfFirstCharacterOfLastWord(sentence, size);                           // Gives us the index of the first character that the last word of the sentence has
        // printf("The index = %d\n", indexLWFC);                                                        // store that in a integer variable for later use
        //  printf("The character at that index = %c\n", sentence[indexLWFC]);                           //

        int check = LocateIndexOfFirstCharacterOfLastWord(sentence, size);                               // also for later comparisons
        // printf("Check is = %d\n",check);

        firstWordIntoNewArray(sentence, ptcR, indexLWFC, check);                                         // extracting the last word of the sentence and including it into the new array
        // for (int i = 0; i < 19; i++)                                                                  // Debug
        //{
        // printf("our character in ptcR = %d\n", ptcR[i]);
        //}

        int whereWasIAgain = whereDidILeft(ptcR);                                                        // Recounts the index where ptcR has no char
        int anothercheck = whereDidILeft(ptcR);                                                          // for Later comparison in function
        // printf("I left of at index %d and %d\n", whereWasIAgain, anothercheck);

        ptcR[whereWasIAgain] = ' ';                                                                      // Put at that index of space because the rest comes there
        ++anothercheck;                                                                                  // we increment both index because there we want the rest of the sentence
        ++whereWasIAgain;

        indexLWFC -= 1;                                                                                  // indexLWFC is still the index of the lastword's first char, need decrement
        //  printf("The index = %c\n", indexLWFC);
        //  printf("indexLWFC still holds %d\n", indexLWFC);

        yeetTheRestInNew(sentence, ptcR, indexLWFC, whereWasIAgain, anothercheck);                       // then we yeet the rest of the sentence it

        printf("the char there%c\n", sentence[size - 2]);
        ptcR[size - 1] = sentence[size - 2];                                                             // '.' or '!' to end sentence
        ptcR[size] = '0';                                                                                // end array with '0'

        for (int i = 0; i < size; i++)
        {
            printf("our character in ptcR = %c\n\n\n", ptcR[i]);
        }
        free(ptcR);
    */
}