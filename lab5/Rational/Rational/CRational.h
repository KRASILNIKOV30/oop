#pragma once
class CRational
{
public:
	CRational() = default;
	CRational(int value);
	CRational(int numerator, int denominator);
	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;

	CRational operator +() const;
	CRational operator -() const;
	CRational& operator +=(CRational const x);
	CRational& operator -=(CRational const x);
	CRational& operator *=(CRational const x);
	CRational& operator /=(CRational const x);

private:
	void Normalize();

private:
	int m_numerator = 0;
	int m_denominator = 1;
};

bool operator ==(CRational const left, CRational const right);
bool operator !=(CRational const left, CRational const right);
bool operator <(CRational const left, CRational const right);
bool operator <=(CRational const left, CRational const right);
bool operator >(CRational const left, CRational const right);
bool operator >=(CRational const left, CRational const right);
CRational operator +(CRational const left, CRational const right);
CRational operator -(CRational const left, CRational const right);
CRational operator *(CRational const left, CRational const right);
CRational operator /(CRational const left, CRational const right);



