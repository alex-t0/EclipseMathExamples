#include "include/Pandigital.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool Pandigital::IsPermutationNumber(long num)
{
    // vector<short> v;
    vector<short> v;

    while (num > 0)
    {
        short remainder = num % 10;

        if (remainder == 0) return false;

        if (find(v.begin(), v.end(), remainder) != v.end())
            return false;

        v.push_back(remainder);
        // v.insert(remainder);
        num = num / 10;
    }

    return true;
}

bool Pandigital::IsFullPandigital(long num)
{
    // vector<short> v;
    vector<int> v;

    while (num > 0)
    {
        short remainder = num % 10;

        // if (remainder == 0) return false;

        if (find(v.begin(), v.end(), remainder) != v.end())
            return false;

        v.push_back(remainder);
        // v.insert(remainder);
        num = num / 10;
    }

    for (unsigned int i = 1; i <= v.size(); i++)
    {
        if (find(v.begin(), v.end(), i) == v.end())
            return false;
    }

    return true;
}

vector<long> Pandigital::GetPermutationNumbers(long num)
{
    vector<long> result;

    for (long i = 1; i <= num; i++)
    {
        if (IsPermutationNumber(i))
            result.push_back(i);
            // result.insert(i);

        if (i % 50000000 == 0)
            std::cout << "i = " << i << std::endl;
    }

    return result;
}

bool Pandigital::TestPandigitalMultiplication(long a, long b, long c)
{
    vector<short> v;

    while (a > 0)
    {
        short remainder = a % 10;

        if (remainder == 0) return false;

        if (find(v.begin(), v.end(), remainder) != v.end())
            return false;

        v.push_back(remainder);
        // v.insert(remainder);
        a = a / 10;
    }

    while (b > 0)
    {
        short remainder = b % 10;

        if (remainder == 0) return false;

        if (find(v.begin(), v.end(), remainder) != v.end())
            return false;

        v.push_back(remainder);
        // v.insert(remainder);
        b = b / 10;
    }

    while (c > 0)
    {
        short remainder = c % 10;

        if (remainder == 0) return false;

        if (find(v.begin(), v.end(), remainder) != v.end())
            return false;

        v.push_back(remainder);
        // v.insert(remainder);
        c = c / 10;
    }

    if (find(v.begin(), v.end(), 1) == v.end())
        return false;
    if (find(v.begin(), v.end(), 2) == v.end())
        return false;
    if (find(v.begin(), v.end(), 3) == v.end())
        return false;
    if (find(v.begin(), v.end(), 4) == v.end())
        return false;
    if (find(v.begin(), v.end(), 5) == v.end())
        return false;
    if (find(v.begin(), v.end(), 6) == v.end())
        return false;
    if (find(v.begin(), v.end(), 7) == v.end())
        return false;
    if (find(v.begin(), v.end(), 8) == v.end())
        return false;
    if (find(v.begin(), v.end(), 9) == v.end())
        return false;

    return true;
}

vector<long> Pandigital::FindPandigitalProducts(vector<long> pd)
{
    vector<long> result;

    for (unsigned int i = 0; i < pd.size(); i++)
    {
        if (pd[i] * pd[i+1] > 987654321)
            return result;

        std::cout << "i = " << i << ", result contains " << result.size() << " items" << std::endl;

        for (unsigned int j = i+1; j < pd.size(); j++)
        {
            long product = pd[i] * pd[j];

            if (TestPandigitalMultiplication(pd[i], pd[j], product) == true)
            {
                cout << "Found result: " << pd[i] << " * " << pd[j] << " = " << product << endl;

                if (find(result.begin(), result.end(), product) == result.end())
                    result.push_back(product);
            }
        }
    }

    return result;
}
