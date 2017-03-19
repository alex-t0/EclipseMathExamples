#include <algorithm>
#include "include/TriangleWords.h"

TriangleWords::TriangleWords()
{
    for (int i=0; i<=1000; i++)
    {
        this->v.push_back((i*(i+1))/2);
    }
}

int TriangleWords::GetLetterCode(std::string letter)
{
    if (letter == "A") return 1;
    if (letter == "B") return 2;
    if (letter == "C") return 3;
    if (letter == "D") return 4;
    if (letter == "E") return 5;
    if (letter == "F") return 6;
    if (letter == "G") return 7;
    if (letter == "H") return 8;
    if (letter == "I") return 9;
    if (letter == "J") return 10;
    if (letter == "K") return 11;
    if (letter == "L") return 12;
    if (letter == "M") return 13;
    if (letter == "N") return 14;
    if (letter == "O") return 15;
    if (letter == "P") return 16;
    if (letter == "Q") return 17;
    if (letter == "R") return 18;
    if (letter == "S") return 19;
    if (letter == "T") return 20;
    if (letter == "U") return 21;
    if (letter == "V") return 22;
    if (letter == "W") return 23;
    if (letter == "X") return 24;
    if (letter == "Y") return 25;
    if (letter == "Z") return 26;

    return 0;
}

bool TriangleWords::TestWord(std::string s)
{
    int sum = 0;
    for (unsigned int i = 0; i < s.size(); i++)
    {
        std::string sp = s.substr(i, 1);
        sum += GetLetterCode(sp);
    }

    if (find(this->v.begin(), this->v.end(), sum) != this->v.end())
        return true;

    return false;
}
