#ifndef _ConsoleTests_Curious_h_
#define _ConsoleTests_Curious_h_

#include <initializer_list>
#include <vector>

class Curious
{
public:
    Curious();
    ~Curious();
    static bool IsCurious(int num);
private:
    std::vector<int> v;
};

#endif
