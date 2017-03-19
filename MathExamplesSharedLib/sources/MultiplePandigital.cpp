#include "include/MultiplePandigital.h"

bool MultiplePandigital::IsMultiplePandigital(int num)
{
    int digitCounter = CountDigits(num);
    // int currentIndex = 1;
    for (int i = 1; i < 9; i++)
    {
        int subnumber = SubNumber(num, 1, i);

        int leftRemainder = num;
        int closedDigits = 0;
        int multiplier = 1;

        bool needContinue = false;

        while (closedDigits < 9)
        {
            int multipliedSubNumber = subnumber * multiplier;

            int multipledSubnumberDigitCounter = CountDigits(multipliedSubNumber);

            int digitsToCompare = SubNumber(num, closedDigits + 1, closedDigits + multipledSubnumberDigitCounter);

            if (multipliedSubNumber != digitsToCompare)
            {
                needContinue = true;
                break;
            }

            closedDigits += multipledSubnumberDigitCounter;
            leftRemainder = SubNumber(leftRemainder, multipledSubnumberDigitCounter + 1, digitCounter - closedDigits);
            multiplier++;
        }

        if (needContinue == true) continue;

        return true;
    }

    return false;
}

int MultiplePandigital::CountDigits(int num)
{
    int digitCounter = 0;

    while (num > 0)
    {
        digitCounter++;

        num /= 10;
    }

    return digitCounter;
}

int MultiplePandigital::SubNumber(int num, int start, int end)
{
    int digitCounter = CountDigits(num);

    if ((start > digitCounter) || (end > digitCounter))
        return 0;

    if (start > end)
    {
        start = start + end;
        end = start - end;
        start = start - end;
    }

    for (int i = 0; i < digitCounter - end; i++)
    {
        num = num / 10;
    }

    int result = 0;
    int multiplier = 1;
    for (int i = start; i <= end; i++)
    {
        result += (num % 10) * multiplier;
        num = num / 10;
        multiplier *= 10;
    }

    return result;
}
