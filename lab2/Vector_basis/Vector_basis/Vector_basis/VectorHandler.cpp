#include "VectorHandler.h"

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
};

void MultElementsByMin(std::vector<float>& v)
{
    float min = *std::ranges::min_element(v);
    for (auto& el : v)
    {
        el *= min;
    }
}

