#include "include/PermutationGenerator.h"
#include <vector>

template class  PermutationGenerator<int>;
template class  PermutationGenerator<long>;

template<typename T>
std::vector<std::vector<T>> PermutationGenerator<T>::GeneratePermutations()
{
    std::vector<std::vector<T>> result;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        T symbol = elements[i];

        std::vector<std::vector<T>> iteration;

        if (result.empty())
        {
            result.push_back({ symbol });
            continue;
        }

        for (unsigned int j = 0; j < result.size(); j++)
        {
            std::vector<T> generator = result[j];

            for (unsigned int k = 0; k <= generator.size(); k++)
            {
                std::vector<T> copy = generator; // full copy

                copy.insert(copy.begin() + k, symbol);

                iteration.push_back(copy);
            }
        }

        result.swap(iteration);
    }

    return result;
}

