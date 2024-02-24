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

// Сделать DigitToChar
char DecimalToChar(int n)
{
    // Убрать abs наверх
    n = std::abs(n);
    if (n < DECIMAL)
    {
        return static_cast<char>('0' + n);
    }
    if (n < MAX_RADIX)
    {
        return static_cast<char>('A' + n - DECIMAL);
    }

    throw std::invalid_argument("Can not convert to char int " + std::to_string(n));
}

// Переименовать
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

std::string ConvertUsingDivision(int n, int radix)
{
    std::string result;
    // Сделать do while
    while (n != 0) 
    {
        int rem = n % radix;
        result += DecimalToChar(rem);
        n /= radix;
    }

    return result;
}

// Упростить функцию (Исправлено)
std::string IntToString(int n, int radix)
{
    bool isNegative = n < 0;
    std::string result = ConvertUsingDivision(n, radix);

    // Убрать \0 костыль (Исправлено)
    if (isNegative)
    {
        result += '-';
    }

    std::ranges::reverse(result);
    // Обра
    return result.empty() ? "0" : result;
}

bool IsNotationsValid(int srcNotation, int dstNotation)
{
    const bool isSrcNotationValid = srcNotation >= MIN_RADIX && srcNotation <= MAX_RADIX;
    const bool isDstNotationValid = dstNotation >= MIN_RADIX && dstNotation <= MAX_RADIX;
    return isSrcNotationValid && isDstNotationValid;
}

bool IsNotationValid(int notation)
{
    return notation >= MIN_RADIX && notation <= MAX_RADIX;
}

//Переименовать (Исправлено)
// Передавать основания с.с. интами (Исправлено)
// Добавить проверку оснований с.с. (Исправлено)
//
std::string ChangeNotation(int srcNotation, int dstNotation, std::string const& value)
{
    if (!(IsNotationValid(srcNotation) && IsNotationValid(dstNotation)))
    {
        throw std::invalid_argument(std::format("source and destination notations must be between {} and {}", MIN_RADIX, MAX_RADIX));
    }
    int n = StringToInt(value, srcNotation);
    return IntToString(n, dstNotation);
}