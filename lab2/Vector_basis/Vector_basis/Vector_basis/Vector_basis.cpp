#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "VectorHandler.h"

int main()
{
    std::vector<float> inputData;
    if (!ParseFloatsToVector(std::cin, inputData))
    {
        std::cout << "Invalid input\n";
        return 1;
    }

    MultElementsByMin(inputData);

    std::ranges::sort(inputData);

    std::ranges::copy(inputData, std::ostream_iterator<float>(std::cout, " "));

    return 0;
}