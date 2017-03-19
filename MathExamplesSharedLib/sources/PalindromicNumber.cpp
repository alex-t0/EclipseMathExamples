#include <vector>
#include "include/PalindromicNumber.h"

PalindromicNumber::PalindromicNumber()
{
}

PalindromicNumber::~PalindromicNumber()
{
}

bool PalindromicNumber::IsPalindromic(int num, int base)
{
    std::vector<int> nums;

    while (num > 0)
    {
        nums.push_back(num % base);
        num = num / base;
    }

    for (int i=0,j=nums.size()-1; i <= j; i++,j--)
    {
        if (nums[i] != nums[j])
            return false;
    }

    return true;
}
