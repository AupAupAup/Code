
char *largestOddNumber(char *num)
{
    if (num[0] == '0')
    {
        return "";
    };
    char max = 0;

    int strinlength = 0;
    for (strinlength; num[strinlength] != '\0'; strinlength++)
    {
    }

    for (int i = strinlength; i != 0; --i)
    {
        int temp = num[i] - '0';

        if (temp % 2 == 0)
        {
            if (num[i] > max)
            {
                max = num[i];
            }
        }
    }

char * ptcpm = (char*)malloc(strinlength);
}