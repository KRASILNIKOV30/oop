#pragma once
#include <iostream>

class CRational
{
public:
	CRational() = default;
	CRational(int value);
	CRational(int numerator, int denominator);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational operator +() const;
	CRational operator -() const;
	CRational& operator +=(CRational const x);
	CRational& operator -=(CRational const x);
	CRational& operator *=(CRational const x);
	CRational& operator /=(CRational const x);
	std::strong_ordering operator<=>(const CRational& rhs) const;
	bool operator ==(CRational const& right) const = default;
private:
	void Normalize();

private:
	int m_numerator = 0;
	int m_denominator = 1;
};

CRational operator +(CRational const left, CRational const right);
CRational operator -(CRational const left, CRational const right);
CRational operator *(CRational const left, CRational const right);
CRational operator /(CRational const left, CRational const right);
std::ostream& operator <<(std::ostream& stream, CRational const x);
std::istream& operator >>(std::istream& stream, CRational& x);



