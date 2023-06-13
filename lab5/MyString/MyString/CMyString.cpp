#include "CMyString.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <cassert>

CMyString::CMyString()
    : m_chars(new char[1])
    , m_length(0)
{
    m_chars[0] = '\0';
}

CMyString::CMyString(const char* pString)
    : m_chars(new char[strlen(pString) + 1])
    , m_length(strlen(pString))
{
    strcpy_s(m_chars, m_length + 1, pString);
}

CMyString::CMyString(const char* pString, size_t length)
    : m_chars(new char[length + 1])
    , m_length(length)
{//использовать std::copy (Исправлено)
    std::copy(pString, pString + length, m_chars);
    m_chars[m_length] = '\0';
}

CMyString::CMyString(char* pString, size_t length, int)
    : m_chars(pString)
    , m_length(length)
{
}

//использовать делигирующий конструктор
CMyString::CMyString(CMyString const& other)
    : m_chars(new char[other.GetLength() + 1])
    , m_length(other.GetLength())
{
    //Написать тест с нулевым символом в середине, исправить (std::copy) (Исправлено)
    std::copy(other.GetStringData(), other.GetStringData() + m_length, m_chars);
    m_chars[m_length] = '\0';
}

CMyString::CMyString(CMyString&& other) noexcept
    : m_chars(other.m_chars)
    , m_length(other.m_length)
{
    other.m_chars = nullptr;
    other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
    : m_chars(new char[stlString.size() + 1])
    , m_length(stlString.size())
{
    //std::copy (Исправлено)
    std::copy(stlString.begin(), stlString.end(), m_chars);
    m_chars[m_length] = '\0';
}

CMyString::~CMyString()
{
    delete[] m_chars;
}

size_t CMyString::GetLength() const noexcept
{
    return m_length;
}

char zeroCode[1] = { '\0' };
const char* CMyString::GetStringData() const noexcept
{
    // не возвращать nullptr (Исправлено)
    if (m_chars == nullptr)
    {
        return zeroCode;
    }
    return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
    //Проверить, что будет при start > m_length (Исправлено)
    if (start >= m_length)
    {
        //лучше out_of_range (ИСправлено)
        throw std::out_of_range("Start index of substring can not be greater than string length");
    }
    size_t remainderLength = m_length - start;
    size_t substrLength = remainderLength < length ? remainderLength : length;
    //утечка памяти (Исправлено)
    //использовать конструктор адрес + длина (Исправлено)
    return CMyString(m_chars + start, substrLength);
}

void CMyString::Clear() noexcept
{
    //возможен double delete (Исправлено)
    delete[] m_chars;
    m_length = 0;
    m_chars = nullptr;
}

CMyString& CMyString::operator=(CMyString const& rhs)
{
    if (&rhs != this)
    {
        //утечка памяти (Исправлено)
        CMyString copyStr(rhs);
        std::swap(m_chars, copyStr.m_chars);
        std::swap(m_length, copyStr.m_length);
    }
    return *this;
}

CMyString& CMyString::operator=(CMyString&& rhs) noexcept
{
    if (&rhs != this)
    {
        delete[] m_chars;
        m_length = rhs.GetLength();
        m_chars = rhs.m_chars;
        rhs.m_chars = nullptr;
        rhs.m_length = 0;
    }
    return *this;
}

CMyString& CMyString::operator+=(CMyString const& rhs)
{
    *this = *this + rhs;
    return *this;
}

const char& CMyString::operator[](size_t index) const
{
    if (index >= m_length)
    {
        throw std::out_of_range("Index out of range");
    }
    return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
    if (index >= m_length)
    {
        throw std::out_of_range("Index out of range");
    }
    return m_chars[index];
}

std::ostream& operator<<(std::ostream& stream, CMyString const& str)
{
    for (size_t i = 0; i < str.GetLength(); i++)
    {
        stream << str[i];
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
    std::vector<char> chars;
    char ch;
    while (stream.get(ch) && ch != ' ' && chars.size() < SIZE_MAX) {
        chars.push_back(ch);
    }
    //утечка памяти (Исправлено)
    char* copyChars = new char[chars.size() + 1];
    std::copy(chars.begin(), chars.end(), copyChars);
    copyChars[chars.size()] = '\0';
    str = std::move(copyChars);
    delete[] copyChars;
    
    return stream;
}

CMyString operator+(CMyString const& lhs, CMyString const& rhs)
{
    if (lhs.GetLength() >= SIZE_MAX - rhs.GetLength())
    {
        throw std::length_error("String cannot be longer than SIZE_MAX");
    }
    //утечка памяти (Исправлено)
    //опечатка в слове (Исправлено)
    size_t length = lhs.GetLength() + rhs.GetLength();
    char* chars = new char[length + 1];
    std::copy(lhs.GetStringData(), lhs.GetStringData() + lhs.GetLength(), chars);
    std::copy(rhs.GetStringData(), rhs.GetStringData() + rhs.GetLength(), chars + lhs.GetLength());
    chars[length] = '\0';
    //явно передавать длину (Исправлено)
    //Создать приватный конструктор (friend) (Исправлено)
    return CMyString(chars, length, int{});
}

bool operator==(CMyString const& lhs, CMyString const& rhs) noexcept
{
    if (lhs.GetLength() != rhs.GetLength())
    {
        return false;
    }
    auto lArr = lhs.GetStringData();
    auto rArr = rhs.GetStringData();
    // std::equal (Исправлено)
    return std::equal(lArr, lArr + lhs.GetLength(), rArr);
}

std::strong_ordering CMyString::operator<=>(CMyString const& rhs) const noexcept
{
    auto lArr = GetStringData();
    auto rArr = rhs.GetStringData();
    //std::lexicographical_compare_three_way (Исправлено)
    return std::lexicographical_compare_three_way(lArr, lArr + m_length, rArr, rArr + rhs.m_length);
}
