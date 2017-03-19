#ifndef _ConsoleTests_Pandigital_h_
#define _ConsoleTests_Pandigital_h_

#include <vector>

using namespace std;

class Pandigital
{
public:
    static bool IsFullPandigital(long num);
    bool IsPermutationNumber(long num);
    vector<long> GetPermutationNumbers(long limit);
    vector<long> FindPandigitalProducts(vector<long> pd);
private:
    bool TestPandigitalMultiplication(long a, long b, long c);
};

#endif
