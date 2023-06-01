#include "CMyString.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

CMyString::CMyString(const char* pString)
    : m_chars(new char[strlen(pString) + 1])
    , m_length(strlen(pString))
{
    strcpy_s(m_chars, m_length + 1, pString);
}

CMyString::CMyString(const char* pString, size_t length)
    : m_chars(new char[length + 1])
    , m_length(length)
{
    for (size_t i = 0; i < m_length; i++)
    {
        m_chars[i] = pString[i];
    }
    m_chars[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
    : m_chars(new char[other.GetLength() + 1])
    , m_length(other.GetLength())
{
    strcpy_s(m_chars, m_length + 1, other.GetStringData());
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
    strcpy_s(m_chars, m_length + 1, stlString.c_str());
}

CMyString::~CMyString()
{
    delete[] m_chars;
}

size_t CMyString::GetLength() const
{
    return m_length;
}

const char* CMyString::GetStringData() const
{
    return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
    size_t remainderLength = m_length - start;
    size_t substrLength = remainderLength < length ? remainderLength : length;
    char* substr = new char[substrLength + 1];
    for (size_t i = 0; i < substrLength; i++)
    {
        substr[i] = m_chars[start + i];
    }
    substr[substrLength] = '\0';

    return CMyString(substr);
}

void CMyString::Clear()
{
    delete[] m_chars;
    m_length = 0;
    m_chars = new char[1] {'\0'};
}

void CMyString::operator=(CMyString const& rhs)
{
    if (&rhs == this)
    {
        return;
    }
    Clear();
    m_length = rhs.GetLength();
    m_chars = new char[m_length + 1];
    strcpy_s(m_chars, m_length + 1, rhs.GetStringData());
}

void CMyString::operator=(CMyString&& rhs) noexcept
{
    if (&rhs == this)
    {
        return;
    }
    Clear();
    m_length = rhs.GetLength();
    m_chars = rhs.m_chars;
    rhs.m_chars = nullptr;
    rhs.m_length = 0;
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
    str.Clear();
    std::vector<char> chars;
    char ch;
    while (stream.get(ch) && ch != ' ' && str.m_length != SIZE_MAX) {
        chars.push_back(ch);
    }
    str.m_length = chars.size();
    str.m_chars = new char[str.m_length + 1];
    std::copy(chars.begin(), chars.end(), str.m_chars);
    str.m_chars[str.m_length] = '\0';
    return stream;
}

CMyString operator+(CMyString const& lhs, CMyString const& rhs)
{
    char* chars = new char[lhs.GetLength() + rhs.GetLength() + 1];
    std::copy(lhs.GetStringData(), lhs.GetStringData() + lhs.GetLength(), chars);
    std::copy(rhs.GetStringData(), rhs.GetStringData() + rhs.GetLength(), chars + lhs.GetLength());
    chars[lhs.GetLength() + rhs.GetLength()] = '\0';

    return CMyString(chars);
}

bool operator==(CMyString const& lhs, CMyString const& rhs)
{
    if (lhs.GetLength() != rhs.GetLength())
    {
        return false;
    }
    auto lArr = lhs.GetStringData();
    auto rArr = rhs.GetStringData();
    for (size_t i = 0; i < lhs.GetLength(); i++)
    {
        if (lArr[i] != rArr[i])
        {
            return false;
        }
    }

    return true;
}

std::strong_ordering CMyString::operator<=>(CMyString const& rhs) const
{
    size_t length = std::min(m_length, rhs.GetLength());
    auto lArr = GetStringData();
    auto rArr = rhs.GetStringData();
    for (size_t i = 0; i < length; i++)
    {
        if ((lArr[i] <=> rArr[i]) != 0)
        {
            return lArr[i] <=> rArr[i];
        }
    }

    return m_length <=> rhs.GetLength();
}
