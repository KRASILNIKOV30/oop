#pragma once
#include <string>
#include <numeric>
#include <iostream>

class CMyString
{
public:
	// ����������� �� ���������
	CMyString() = default;

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� �� 
	// ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString&& other) noexcept;

	// �����������, ���������������� ������ ������� �� 
	// ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength()const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData()const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	void operator=(CMyString const& rhs);
	void operator=(CMyString&& rhs) noexcept;
	CMyString& operator+=(CMyString const& rhs);
	std::strong_ordering operator<=>(CMyString const& rhs) const;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::istream& operator>>(std::istream& stream, CMyString& str);

private:
	char* m_chars = new char[1] {'\0'};
	size_t m_length = 0;
};

CMyString operator+(CMyString const& lhs, CMyString const& rhs);
bool operator==(CMyString const& lhs, CMyString const& rhs);
std::ostream& operator<<(std::ostream& stream, CMyString const& str);
std::istream& operator>>(std::istream& stream, CMyString& str);
