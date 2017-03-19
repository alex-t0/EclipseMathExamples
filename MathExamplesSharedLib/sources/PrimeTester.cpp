#include "include/PrimeTester.h"
#include <cmath>

PrimeTester::PrimeTester()
{
}

PrimeTester::~PrimeTester()
{
}

bool PrimeTester::IsPrime(long n)
{
    if (n == 1) return false;

    if (n < 4) return true;

    if (n % 2 == 0) return false;

    if (n < 9) return true;

    if (n % 3 == 0) return false;

    long r = floor(sqrt(n));

    long f = 5;
    while (f <= r)
    {
        if ((n % f == 0) || ((n % (f+2)) == 0))
            return false;

        f += 6;
    }

    return true;
}

long PrimeTester::RotateInt(long n)
{
    int numDigits = 0;
    int ncopy = n;

    while (ncopy > 0)
    {
        numDigits++;
        ncopy = ncopy / 10;
    }

    int power = 1;

    for (int i = 1; i < numDigits; i++)
        power *= 10;

    return (n % 10) * power + (n/10);
}
