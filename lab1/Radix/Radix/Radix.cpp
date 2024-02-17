#include "Radix.h"
#include <cctype>
#include <algorithm>

constexpr int DECIMAL = 10;

std::string Capitalize(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::toupper(c); }
    );
    return s;
}

int StringToInt(std::string const& str, int radix)
{
    return std::stoi(str, nullptr, radix);
}

std::string IntToString(int n, int radix)
{
    char buffer[sizeof(int) * 8 + 1];
    _itoa_s(n, buffer, radix);
    return buffer;
}

std::string Radix(std::string const& srcNotation, std::string const& dstNotation, std::string const& value)
{
    int srcRadix = StringToInt(srcNotation, DECIMAL);
    int dstRadix = StringToInt(dstNotation, DECIMAL);
    int n = StringToInt(value, srcRadix);
    return Capitalize(IntToString(n, dstRadix));
}