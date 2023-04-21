#include "../../../external/catch2/catch.hpp"
#include "../Task2/Calculator.h"

//TEST_CASE("Calculator does not have any variables and functions")
//{
//	Calculator calc;
//	CHECK(calc.GetVars().size() == 0);
//	CHECK(calc.GetFunctions().size() == 0);
//}

SCENARIO("Variable definition")
{
	GIVEN("Empty calculator")
	{
		Calculator calc;

		WHEN("I define a variable")
		{
			CHECK(calc.DefineVar("t"));

			THEN("Calculator has one variable")
			{
				REQUIRE(calc.GetVars().size() == 1);
			}

			AND_THEN("Var has a name and NAN value")
			{
				auto var = calc.FindVar("t");
				CHECK(var.has_value());
				CHECK(calc.GetVars()[0].GetName() == "t");
				CHECK(isnan(calc.GetVars()[0].GetValue()));
			}

			AND_THEN("I can find variable by name")
			{
				auto var = calc.FindVar("t");
				REQUIRE(var.has_value());
				CHECK(var->GetName() == "t");
				CHECK(isnan(var->GetValue()));
			}
		}	
	}
}

SCENARIO("Function without operations definition")
{
	GIVEN("Empty calculator")
	{
		Calculator calc;

		/*WHEN("I define a function with undeclared variable")
		{
			CHECK(!calc.DefineFunction("MyFunc", "x"));

			THEN("Calculator has no functions")
			{
				REQUIRE(calc.GetFunctions().size() == 0);
			}
		}*/

		WHEN("I define a function with declared variable")
		{
			calc.DefineVar("x");
			REQUIRE(calc.DefineFunction("MyFunc", "x"));

			THEN("Calculator has one function")
			{
				CHECK(calc.GetFunctions().size() == 1);
			}

			AND_THEN("Function has a name and NAN value")
			{
				CHECK(calc.GetFunctions()[0].GetName() == "MyFunc");
				CHECK(isnan(calc.GetFunctions()[0].GetValue()));
			}

			AND_THEN("I can find function by name")
			{
				auto function = calc.FindFunction("MyFunc");
				REQUIRE(function.has_value());
				CHECK(function->GetName() == "MyFunc");

				WHEN("I change variables value")
				{
					CHECK(calc.ChangeVarValue("x", 10));

					THEN("Functions value changes too")
					{
						CHECK(IsEquals(function->GetValue(), 10));
					}
				}
			}
		}
	}
}