#include "include/Curious.h"

Curious::Curious()
{
}

Curious::~Curious()
{
}

bool Curious::IsCurious(int num)
{
    int sum = 0;

    int save = num;

    while (num > 0)
    {
        int rem = num % 10;

        if (rem == 0 || rem == 1) sum += 1;
        if (rem == 2) sum += 2;
        if (rem == 3) sum += 6;
        if (rem == 4) sum += 24;
        if (rem == 5) sum += 120;
        if (rem == 6) sum += 720;
        if (rem == 7) sum += 5040;
        if (rem == 8) sum += 40320;
        if (rem == 9) sum += 362880;

        num = num / 10;
    }

    return sum == save;
}
