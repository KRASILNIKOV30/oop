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

		WHEN("I define a variable")
		{
			CHECK(calc.DefineVar("x"));

			THEN("Calculator has one variable")
			{
				REQUIRE(calc.GetVars().size() == 1);
			}

			AND_THEN("Var has a name and NAN value")
			{
				CHECK(calc.GetVars()[0].GetName() == "x");
				CHECK(isnan(calc.GetVars()[0].GetValue()));
			}

			AND_THEN("I can find variable by name")
			{
				std::optional<Var> var = calc.FindVar("x");
				REQUIRE(var.has_value());
				CHECK(var.value().GetName() == "x");
			}
		}	
	}
}

SCENARIO("Function without operations definition")
{
	GIVEN("Empty calculator")
	{
		Calculator calc;

		WHEN("I define a function with undeclared variable")
		{
			CHECK(!calc.DefineFunction("MyFunc", "x"));

			THEN("Calculator has no functions")
			{
				CHECK(calc.GetFunctions().size() == 0);
			}
		}

		WHEN("I define a function with declared variable")
		{
			calc.DefineVar("x");
			REQUIRE(calc.DefineFunction("MyFunc", "x"));

			THEN("Calculator has one function")
			{
				CHECK(calc.GetFunctions().size() == 1);
			}

			AND_THEN("Function has a name")
			{
				CHECK(calc.GetFunctions()[0].GetName() == "MyFunc");
			}

			AND_THEN("I can find function by name")
			{
				auto function = calc.FindFunction("MyFunc");
				REQUIRE(function.has_value());
				CHECK(function.value().GetName() == "MyFunc");
			}
		}
	}
}

TEST_CASE("I can get value of declared function")
{
	Calculator calc;
	calc.DefineVar("x");
	CHECK(calc.DefineFunction("MyFunc", "x"));
	Function func = calc.FindFunction("MyFunc").value();
	CHECK(func.GetValue());
}