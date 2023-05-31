#include "CMyString.h"

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
    m_length = rhs.GetLength();
    m_chars = new char[m_length + 1];
    strcpy_s(m_chars, m_length + 1, rhs.GetStringData());
}
