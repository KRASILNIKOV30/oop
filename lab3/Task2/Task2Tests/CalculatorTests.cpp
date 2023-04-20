#include "../../../external/catch2/catch.hpp"
#include "../Task2/Calculator.h"

TEST_CASE("Calculator does not have any variables and functions")
{
	Calculator calc;
	CHECK(calc.GetVars().size() == 0);
	CHECK(calc.GetFunctions().size() == 0);
}

SCENARIO("Variable definition")
{
	GIVEN("Empty calculator")
	{
		Calculator calc;

		WHEN("I define variable")
		{
			CHECK(calc.DefineVar("x"));

			THEN("Calculator has one variable")
			{
				CHECK(calc.GetVars().size() == 1);
			}
		}	
	}
}