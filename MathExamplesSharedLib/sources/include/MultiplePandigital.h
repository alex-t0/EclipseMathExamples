#ifndef _ConsoleTests_MultiplePandigital_h_
#define _ConsoleTests_MultiplePandigital_h_

class MultiplePandigital
{
public:
    static bool IsMultiplePandigital(int num);
    static int SubNumber(int num, int start, int end);
private:
    static int CountDigits(int num);

};

#endif
