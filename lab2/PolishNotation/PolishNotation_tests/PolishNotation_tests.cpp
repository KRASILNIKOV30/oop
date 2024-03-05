#include "../../../external/catch2/catch.hpp"
#include <sstream>
#include "../PolishNotation/PolishNotation.h"

SCENARIO("Calculate polish notation positive tests")
{
	GIVEN("Operation with one argument")
	{
		std::istringstream input("(+ 7)");

		THEN("The value of expression is equal to the argument")
		{
			CHECK(CalculatePolish(input) == 7);
		}
	}

	GIVEN("Operation with many arguments")
	{
		std::istringstream input("(/ 32 4 2)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 4);
		}
	}

	GIVEN("Expression with one argument, which is an expression")
	{
		std::istringstream input("(- (* 1 3 8))");

		THEN("The outer operation does not affect the value of the expression inside")
		{
			CHECK(CalculatePolish(input) == 24);
		}
	}

	GIVEN("Expression with one argument and expression inside")
	{
		std::istringstream input("(- 25 (* 1 3 8))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with one expression and argument inside")
	{
		std::istringstream input("(- (* 1 3 8) 23)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with two expressions inside")
	{
		std::istringstream input("(- (* 1 3 8) (+ 20 3))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Double nested expression")
	{
		std::istringstream input("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2)))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 33);
		}
	}

	GIVEN("Strongly nested expression")
	{
		std::istringstream input("(* 2 (* 2 (* 2 (* 2 (* 2 (* 2))))))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 64);
		}
	}

	GIVEN("Expression with negative argument")
	{
		std::istringstream input("(+ -2 3)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with negative argument and negative result")
	{
		std::istringstream input("(+ -2 (* -1 (/ 27 -9)) -2)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == -1);
		}
	}

	GIVEN("Expression with fractions")
	{
		std::istringstream input("(+ 0.5 0.5)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with fractions (extended)")
	{
		std::istringstream input("(/ (+ -20.33 4.13 6.20) (* (/ 32.5 16.25) 2))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == -2.5);
		}
	}
}