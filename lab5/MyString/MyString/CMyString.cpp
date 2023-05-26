#include "CMyString.h"

CMyString::CMyString(const char* pString)
    : m_chars(new char[strlen(pString) + 1] {})
    , m_length(strlen(pString))
{
    strcpy_s(m_chars, m_length + 1, pString);
}

CMyString::CMyString(const char* pString, size_t length)
{
}

CMyString::CMyString(CMyString const& other)
{
}

CMyString::CMyString(CMyString&& other)
{
}

CMyString::CMyString(std::string const& stlString)
{
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
    return CMyString();
}

void CMyString::Clear()
{
}
