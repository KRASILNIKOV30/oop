#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool ParseFloatsToVector(std::istream& input, std::vector<float>& v)
{
    float value = 0.f;

    while (input >> value)
    { 
        v.push_back(value);
    };

    if (!input.eof())
    {
        return false;
    };

    return !v.empty();
}

void MultElementsByMin(std::vector<float>& v)
{
    float min = *std::ranges::min_element(v); 
    for (auto& el : v)
    {
        el *= min;
    }
}

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