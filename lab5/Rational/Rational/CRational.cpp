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

bool operator !=(CRational const left, CRational const right)
{
	return !(left == right);
}

bool operator<(CRational const left, CRational const right)
{
	int commonDenominator = std::lcm(left.GetDenominator(), right.GetDenominator());
	int leftNumerator = left.GetNumerator() * commonDenominator / left.GetDenominator();
	int rightNumerator = right.GetNumerator() * commonDenominator / right.GetDenominator();

	return leftNumerator < rightNumerator;
}

bool operator<=(CRational const left, CRational const right)
{
	int commonDenominator = std::lcm(left.GetDenominator(), right.GetDenominator());
	int leftNumerator = left.GetNumerator() * commonDenominator / left.GetDenominator();
	int rightNumerator = right.GetNumerator() * commonDenominator / right.GetDenominator();

	return leftNumerator <= rightNumerator;
}

bool operator>(CRational const left, CRational const right)
{
	int commonDenominator = std::lcm(left.GetDenominator(), right.GetDenominator());
	int leftNumerator = left.GetNumerator() * commonDenominator / left.GetDenominator();
	int rightNumerator = right.GetNumerator() * commonDenominator / right.GetDenominator();

	return leftNumerator > rightNumerator;
}

bool operator>=(CRational const left, CRational const right)
{
	int commonDenominator = std::lcm(left.GetDenominator(), right.GetDenominator());
	int leftNumerator = left.GetNumerator() * commonDenominator / left.GetDenominator();
	int rightNumerator = right.GetNumerator() * commonDenominator / right.GetDenominator();

	return leftNumerator >= rightNumerator;
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
	int commonDenominator = std::lcm(left.GetDenominator(), right.GetDenominator());
	int leftNumerator = left.GetNumerator() * commonDenominator / left.GetDenominator();
	int rightNumerator = right.GetNumerator() * commonDenominator / right.GetDenominator();
	return CRational(leftNumerator - rightNumerator, commonDenominator);
}

CRational operator*(CRational const left, CRational const right)
{
	return CRational(left.GetNumerator() * right.GetNumerator(), left.GetDenominator() * right.GetDenominator());
}

CRational operator/(CRational const left, CRational const right)
{
	return CRational(left.GetNumerator() * right.GetDenominator(), left.GetDenominator() * right.GetNumerator());
}

CRational& CRational::operator+=(CRational const x)
{
	int commonDenominator = std::lcm(GetDenominator(), x.GetDenominator());
	int leftNumerator = GetNumerator() * commonDenominator / GetDenominator();
	int rightNumerator = x.GetNumerator() * commonDenominator / x.GetDenominator();
	m_numerator = leftNumerator + rightNumerator;
	m_denominator = commonDenominator;
	Normalize();

	return *this;
}

CRational& CRational::operator-=(CRational const x)
{
	int commonDenominator = std::lcm(GetDenominator(), x.GetDenominator());
	int leftNumerator = GetNumerator() * commonDenominator / GetDenominator();
	int rightNumerator = x.GetNumerator() * commonDenominator / x.GetDenominator();
	m_numerator = leftNumerator - rightNumerator;
	m_denominator = commonDenominator;
	Normalize();

	return *this;
}

CRational& CRational::operator*=(CRational const x)
{
	m_numerator *= x.GetNumerator();
	m_denominator *= x.GetDenominator();
	Normalize();

	return *this;
}

CRational& CRational::operator/=(CRational const x)
{
	m_numerator *= x.GetDenominator();
	m_denominator *= x.GetNumerator();
	Normalize();

	return *this;
}
