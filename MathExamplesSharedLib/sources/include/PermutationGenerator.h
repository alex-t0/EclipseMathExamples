#ifndef _ConsoleTests_PermutationGenerator_h_
#define _ConsoleTests_PermutationGenerator_h_

#include <vector>
#include <initializer_list>

template<typename T>
class PermutationGenerator
{
public:
    PermutationGenerator(std::initializer_list<T> l) : elements {l} {}
    std::vector<std::vector<T>> GeneratePermutations();
private:
    std::vector<T> elements;
};

#endif
