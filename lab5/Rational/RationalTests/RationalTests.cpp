#include "../../../external/catch2/catch.hpp"
#include "../Rational/CRational.h"
#include "../Rational/Common.h"

SCENARIO("Rational constructing")
{
	WHEN("Constructing rational without any params")
	{
		CRational x;

		THEN("Rational is equal to 0")
		{
			CHECK(x.GetNumerator() == 0);
			CHECK(x.GetDenominator() == 1);
			CHECK(x.ToDouble() == 0);
		}
	}

	WHEN("Constructing rational with one param 5")
	{
		CRational x = 5;

		THEN("Rational is equal to 5")
		{
			CHECK(x.GetNumerator() == 5);
			CHECK(x.GetDenominator() == 1);
			CHECK(x.ToDouble() == 5);
		}
	}

	WHEN("Constructing rational with two params 1 and 2")
	{
		CRational x = { 1, 2 };

		THEN("Rational is equal to 0.5")
		{
			CHECK(x.GetNumerator() == 1);
			CHECK(x.GetDenominator() == 2);
			CHECK(IsEquals(x.ToDouble(), 0.5));
		}
	}

	WHEN("Constructing rational with two params 9 and 12")
	{
		CRational x = { 9, 12 };

		THEN("Rational is equal to 0.75")
		{
			CHECK(x.GetNumerator() == 3);
			CHECK(x.GetDenominator() == 4);
			CHECK(IsEquals(x.ToDouble(), 0.75));
		}
	}
	
	WHEN("Constructing rational with negative numerator")
	{
		CRational x = { -1, 4 };

		THEN("Rational is equal to -0.25")
		{
			CHECK(x.GetNumerator() == -1);
			CHECK(x.GetDenominator() == 4);
			CHECK(IsEquals(x.ToDouble(), -0.25));
		}
	}

	WHEN("Constructing rational with negative denomerator")
	{
		CRational x = { 1, -4 };

		THEN("Rational is equal to -0.25")
		{
			CHECK(x.GetNumerator() == -1);
			CHECK(x.GetDenominator() == 4);
			CHECK(IsEquals(x.ToDouble(), -0.25));
		}
	}

	WHEN("Constructing rational with negative numerator and denomerator")
	{
		CRational x = { -1, -4 };

		THEN("Rational is equal to 0.25")
		{
			CHECK(x.GetNumerator() == 1);
			CHECK(x.GetDenominator() == 4);
			CHECK(IsEquals(x.ToDouble(), 0.25));
		}
	}
}

TEST_CASE("Check unary operator +")
{
	CRational x = { 3, 4 };
	CHECK(x == +x);
}

TEST_CASE("Check unary operator -")
{
	CRational x = { 3, 4 };
	CHECK(-x == CRational(-3, 4));
}

TEST_CASE("Check operator +")
{
	CHECK(CRational(1, 2) + CRational(1, 6) == CRational(2, 3));
	CHECK(CRational(1, 2) + 1 == CRational(3, 2));
	CHECK(1 + CRational(1, 2) == CRational(3, 2));
}

TEST_CASE("Check operator -")
{
	CHECK(CRational(1, 2) - CRational(1, 6) == CRational(1, 3));
	CHECK(CRational(1, 2) - 1 == - CRational(1, 2));
	CHECK(1 - CRational(1, 2) == CRational(1, 2));
}

TEST_CASE("Check operator +=")
{
	CHECK((CRational(1, 2) += CRational(1, 6)) == CRational(2, 3));
	CHECK((CRational(1, 2) += 1) == CRational(3, 2));
}

TEST_CASE("Check operator -=")
{
	CHECK((CRational(1, 2) -= CRational(1, 6)) == CRational(1, 3));
	CHECK((CRational(1, 2) -= 1) == -CRational(1, 2));
}

TEST_CASE("Check operator *")
{
	CHECK(CRational(1, 2) * CRational(2, 3) == CRational(1, 3));
	CHECK(CRational(1, 2) * (-3) == -CRational(3, 2));
	CHECK(7 * CRational(2, 3) == CRational(14, 3));
}

TEST_CASE("Check operator /")
{
	CHECK(CRational(1, 2) / CRational(2, 3) == CRational(3, 4));
	CHECK(CRational(1, 2) / 5 == CRational(1, 10));
	CHECK(7 / CRational(2, 3) == CRational(21, 2));
}

TEST_CASE("Check operator *=")
{
	CHECK((CRational(1, 2) *= CRational(2, 3)) == CRational(1, 3));
	CHECK((CRational(1, 2) *= 3) == CRational(3, 2));
}

TEST_CASE("Check operator /=")
{
	CHECK((CRational(1, 2) /= CRational(2, 3)) == CRational(3, 4));
	CHECK((CRational(1, 2) /= 3) == CRational(1, 6));
	CHECK((CRational(3, 4) /= CRational(3, 8)) == 2);
}

TEST_CASE("Check operator ==")
{
	CHECK(CRational(1, 2) == CRational(1, 2));
	CHECK(!(CRational(1, 2) == CRational(2, 3)));
	CHECK(CRational(4, 1) == 4);
	CHECK(!(CRational(1, 2) == 7));
	CHECK(3 == CRational(3, 1));
	CHECK(!(3 == CRational(2, 3)));
}

TEST_CASE("Check operator !=")
{
	CHECK(!(CRational(1, 2) != CRational(1, 2)));
	CHECK((CRational(1, 2) != CRational(2, 3)));
	CHECK(!(CRational(4, 1) != 4));
	CHECK((CRational(1, 2) != 7));
	CHECK(!(3 != CRational(3, 1)));
	CHECK((3 != CRational(2, 3)));
}

TEST_CASE("Check operators <, <=, >, >=")
{
	CHECK(CRational(1, 2) >= CRational(1, 3));
	CHECK(!(CRational(1, 2) <= CRational(1, 3)));
	CHECK(CRational(3, 1) > 2);
	CHECK(CRational(1, 2) < 7);
	CHECK(3 <= CRational(7, 2));
	CHECK(!(3 >= CRational(8, 2)));
}

