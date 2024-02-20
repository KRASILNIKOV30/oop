#include "Radix.h"
#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <format>

constexpr int DECIMAL = 10;
constexpr int MAX_RADIX = 36;
constexpr int MIN_RADIX = 2;
constexpr int MAXINT = std::numeric_limits<int>::max();
constexpr int MININT = std::numeric_limits<int>::min();

int CharToDecimal(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    if (ch >= 'A' && ch <= 'Z')
    {
        return ch - 'A' + DECIMAL;
    }

    throw std::invalid_argument("Can not convert to int char: " + ch);
}

char DecimalToChar(int n)
{
    n = std::abs(n);
    if (n < DECIMAL)
    {
        return '0' + n;
    }
    if (n < MAX_RADIX)
    {
        return 'A' + n - DECIMAL;
    }

    throw std::invalid_argument("Can not convert to char int " + std::to_string(n));
}

bool IsSumOverflowInt(int a, int b, int radix)
{
    bool moreThanMaxInt = a > 0 && b > MAXINT - a * radix;
    bool lessThanMinInt = a < 0 && b > a * radix - MININT;
    return moreThanMaxInt || lessThanMinInt;
}

int StringToInt(std::string const& str, int radix)
{
    int result = 0;
    int sign = 1;
    for (auto ch : str)
    {
        if (ch == '-')
        {
            sign = -1;
            continue;
        }
        int n = CharToDecimal(ch);
        if (IsSumOverflowInt(result, n, radix))
        {
            throw std::invalid_argument("Overflow occured");
        }
        // Убавлять, если число отрицательное (Исправлено)
        result = result * radix + n * sign;
    }
    return result;
}

// Упростить функцию (Исправлено)
std::string IntToString(int n, int radix)
{
    bool isNegative = false;
    std::string str;
    int number = n;

    while (number != 0) {
        int rem = number % radix;
        str += DecimalToChar(rem);
        number /= radix;
    }

    // Убрать \0 костыль (Исправлено)
    if (n < 0)
    {
        str += '-';
    }

    std::ranges::reverse(str);
    return str;
}

void VerifyNotations(int srcNotation, int dstNotation)
{
    const bool isSrcNotationValid = srcNotation >= MIN_RADIX && srcNotation <= MAX_RADIX;
    const bool isDstNotationValid = dstNotation >= MIN_RADIX && dstNotation <= MAX_RADIX;
    if (!isSrcNotationValid || !isDstNotationValid)
    {
        throw std::invalid_argument(std::format("source and destination notations must be between {} and {}", MIN_RADIX, MAX_RADIX));
    }
}

//Переименовать
// Передавать основания с.с. интами 
// Добавить проверку оснований с.с.
// 
std::string ChangeNotation(int srcNotation, int dstNotation, std::string const& value)
{
    VerifyNotations(srcNotation, dstNotation);
    int n = StringToInt(value, srcNotation);
    return IntToString(n, dstNotation);
}