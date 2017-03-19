#ifndef _ConsoleTests_TriangleWords_h_
#define _ConsoleTests_TriangleWords_h_

#include <vector>
#include <string>

class TriangleWords
{
public:
    TriangleWords();
    bool TestWord(const std::string s);
private:
    std::vector<int> v = {};
    int GetLetterCode(const std::string letter);
};

#endif
