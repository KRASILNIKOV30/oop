#include "../../../external/catch2/catch.hpp"
#include "../Task2/Calculator.h"

TEST_CASE("Calculator does not have any variables and functions after definition")
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

		WHEN("I define a function with declared variable")
		{
			REQUIRE(calc.DefineVar("x"));
			REQUIRE(calc.DefineFunction("MyFunc", "x"));

			THEN("Calculator has one function")
			{
				REQUIRE(calc.GetFunctions().size() == 1);
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

		WHEN("I define a function with undeclared variable")
		{
			CHECK(!calc.DefineFunction("MyFunc", "x"));

			THEN("Calculator has no functions")
			{
				REQUIRE(calc.GetFunctions().size() == 0);
			}
		}
	}
}

SCENARIO("Function with operation definition")
{
	GIVEN("Empty calculator")
	{
		Calculator calc;

		WHEN("I define a function that additing two vars")
		{
			REQUIRE(calc.DefineVar("x"));
			REQUIRE(calc.DefineVar("y"));
			REQUIRE(calc.DefineFunction("XPlusY", "x", "+", "y"));

			THEN("Calculator has one function")
			{
				REQUIRE(calc.GetFunctions().size() == 1);
			}

			AND_THEN("Function has a name and NAN value")
			{
				CHECK(calc.GetFunctions()[0].GetName() == "XPlusY");
				CHECK(isnan(calc.GetFunctions()[0].GetValue()));

				WHEN("I define one variable")
				{
					calc.ChangeVarValue("x", 1);

					THEN("Function has NAN value")
					{
						CHECK(isnan(calc.GetFunctions()[0].GetValue()));
					}
				}
			}

			AND_THEN("I can find function by name")
			{
				auto function = calc.FindFunction("XPlusY");
				REQUIRE(function.has_value());
				CHECK(function->GetName() == "XPlusY");

				WHEN("I define varibles")
				{
					REQUIRE(calc.ChangeVarValue("x", 1));
					REQUIRE(calc.ChangeVarValue("y", 2));

					THEN("Function can add this variables")
					{
						CHECK(IsEquals(function->GetValue(), 3));
					}

					WHEN("I change variables value")
					{
						CHECK(calc.ChangeVarValue("x", 10));

						THEN("Functions value changes too")
						{
							CHECK(IsEquals(function->GetValue(), 12));
						}
					}
				}
			}
		}
	}
}

SCENARIO("Function that depends on another functions definition")
{
	GIVEN("Empty calculator")
	{
		Calculator calc;

		WHEN("I define a function that depends on another functions")
		{
			calc.DefineVar("x");
			calc.ChangeVarValue("x", 2);
			calc.DefineVar("y");
			calc.ChangeVarValue("y", 1);
			calc.DefineFunction("XPlusY", "x", "+", "y");
			calc.DefineFunction("XMinusY", "x", "-", "y");
			REQUIRE(calc.DefineFunction("MultFns", "XPlusY", "*", "XMinusY"));
			REQUIRE(calc.DefineFunction("FnCopy", "MultFns"));

			THEN("I can get function value")
			{
				auto function = calc.FindFunction("FnCopy");
				CHECK(IsEquals(function->GetValue(), 3));

				WHEN("I change variables value")
				{
					CHECK(calc.ChangeVarValue("x", 10));
					CHECK(calc.ChangeVarValue("y", 2));

					THEN("Functions value changes too")
					{
						CHECK(IsEquals(function->GetValue(), 96));
					}
				}
			}
		}
	}
}