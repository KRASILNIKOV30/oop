﻿#include "../../../external/catch2/catch.hpp"
#include "../Rational/CRational.h"
#include "../Rational/Common.h"
#include <sstream>

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

	WHEN("Constructing rational with zero denomerator")
	{
		THEN("Invalid argument exception is thrown")
		{
			CHECK_THROWS_AS(CRational(3, 0), std::invalid_argument);
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
	CRational x(1, 2);
	CRational y(1, 2);
	CHECK(std::addressof(x += y) == std::addressof(x));
	CHECK((CRational(1, 2) += CRational(1, 6)) == CRational(2, 3));
	CHECK((CRational(1, 2) += 1) == CRational(3, 2));
}

TEST_CASE("Check operator -=")
{
	CRational x(1, 2);
	CRational y(1, 2);
	CHECK(std::addressof(x -= y) == std::addressof(x));
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
	//std::addressof(a *= b) == std::adressof(a); (Дополнено)
	CRational x(1, 2);
	CRational y(1, 2);
	CHECK(std::addressof(x *= y) == std::addressof(x));
	CHECK((CRational(1, 2) *= CRational(2, 3)) == CRational(1, 3));
	CHECK((CRational(1, 2) *= 3) == CRational(3, 2));
}

TEST_CASE("Check operator /=")
{
	CRational x(1, 2);
	CRational y(1, 2);
	CHECK(std::addressof(x /= y) == std::addressof(x));
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
	CHECK(!(CRational(1, 4) >= CRational(1, 3)));

	CHECK(!(CRational(1, 2) <= CRational(1, 3)));
	CHECK(CRational(1, 4) <= CRational(1, 3));

	//дополнить тесты(Исправлено)
	CHECK(CRational(3, 1) > 2);
	CHECK(!(CRational(3, 5) > 2));

	CHECK(CRational(1, 2) < 7);
	CHECK(!(CRational(1, 2) < -1));

	CHECK(3 <= CRational(7, 2));
	CHECK(!(3 <= CRational(7, 3)));

	CHECK(!(3 >= CRational(8, 2)));
	CHECK(3 >= CRational(8, 3));
}

TEST_CASE("Check operator >> and <<")
{
	CRational x(7, 15);
	CRational y;
	std::stringstream stream = std::stringstream();
	stream << x;
	CHECK(stream.str() == "7/15");
	stream >> y;
	CHECK(y.GetNumerator() == 7);
	CHECK(y.GetDenominator() == 15);
}

TEST_CASE("A fraction can be converted into a compound")
{
	CRational x(9, 4);
	auto compoundFrac = x.ToCompoundFraction();
	CHECK(compoundFrac.first == 2);
	CHECK(compoundFrac.second == CRational(1, 4));

	compoundFrac = (-x).ToCompoundFraction();
	CHECK(compoundFrac.first == -2);
	CHECK(compoundFrac.second == -CRational(1, 4));

	compoundFrac = CRational(3, 4).ToCompoundFraction();
	CHECK(compoundFrac.first == 0);
	CHECK(compoundFrac.second == CRational(3, 4));
}

