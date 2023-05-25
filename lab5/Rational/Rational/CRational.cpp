#include "CRational.h"
#include <numeric>
#include <stdexcept>

CRational::CRational(int value)
	: m_numerator(value)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		std::invalid_argument e{"denominator cannot be zero"};
		throw e;
	}
	Normalize();
	if (m_denominator < 0) 
	{
		m_denominator *= -1;
		m_numerator *= -1;
	}
}

void CRational::Normalize()
{
	int gcd = std::gcd(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

bool operator ==(CRational const left, CRational const right)
{
	return left.GetNumerator() == right.GetNumerator() && left.GetDenominator() == right.GetDenominator();
}

bool operator<(CRational const left, CRational const right)
{
	return (left.GetNumerator() * right.GetDenominator()) < (right.GetNumerator() * left.GetDenominator());
}

bool operator<=(CRational const left, CRational const right)
{
	return left < right || left == right;
}

bool operator>(CRational const left, CRational const right)
{
	return !(left <= right);
}

bool operator>=(CRational const left, CRational const right)
{
	return !(left < right);
}

CRational operator +(CRational const left, CRational const right)
{
	int commonDenominator = std::lcm(left.GetDenominator(), right.GetDenominator());
	int leftNumerator = left.GetNumerator() * commonDenominator / left.GetDenominator();
	int rightNumerator = right.GetNumerator() * commonDenominator / right.GetDenominator();
	return CRational(leftNumerator + rightNumerator, commonDenominator);
}

CRational operator -(CRational const left, CRational const right)
{
	return left + (-right);
}

CRational operator*(CRational const left, CRational const right)
{
	return CRational(left.GetNumerator() * right.GetNumerator(), left.GetDenominator() * right.GetDenominator());
}

CRational operator/(CRational const left, CRational const right)
{
	return CRational(left.GetNumerator() * right.GetDenominator(), left.GetDenominator() * right.GetNumerator());
}

std::ostream& operator<<(std::ostream& stream, CRational const x)
{
	stream << x.GetNumerator() << "/" << x.GetDenominator();
	
	return stream;
}

std::istream& operator>>(std::istream& stream, CRational& x)
{
	int numerator;
	int denominator;
	if (stream >> numerator && stream.get() == '/' && stream >> denominator)
	{
		x = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}

CRational& CRational::operator+=(CRational const x)
{
	return *this = *this + x;
}

CRational& CRational::operator-=(CRational const x)
{
	return (*this += (-x));
}

CRational& CRational::operator*=(CRational const x)
{
	return *this = *this * x;
}

CRational& CRational::operator/=(CRational const x)
{
	return *this = *this / x;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int intPart = (int)ToDouble();
	CRational fracPart = *this - intPart;

	return std::pair<int, CRational>(intPart, fracPart);
}
