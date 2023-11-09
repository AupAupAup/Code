


unsigned deldigits(unsigned num, unsigned short div)
{

    if (num == 0)
    {
        return 0;
    }

    if (num % 10 % div == 0)
    {
        return deldigits(num / 10, div);
    }
    else
    {
        return num % 10 + deldigits(num / 10, div) * 10;
    }
}