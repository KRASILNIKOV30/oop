#pragma once
#include <string>
#include <numeric>
#include <iostream>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString(std::string const& stlString);
	~CMyString();

	size_t GetLength()const noexcept;
	const char* GetStringData()const noexcept;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator=(CMyString const& rhs);
	CMyString& operator=(CMyString&& rhs) noexcept;
	CMyString& operator+=(CMyString const& rhs);
	std::strong_ordering operator<=>(CMyString const& rhs) const noexcept;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

private:
	char* m_chars;
	size_t m_length;
};

CMyString operator+(CMyString const& lhs, CMyString const& rhs);
bool operator==(CMyString const& lhs, CMyString const& rhs) noexcept;
std::ostream& operator<<(std::ostream& stream, CMyString const& str);
std::istream& operator>>(std::istream& stream, CMyString& str);
