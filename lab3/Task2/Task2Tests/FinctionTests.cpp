#include "../../../external/catch2/catch.hpp"
#include "../Task2/Function.h"
#include "../Task2/Var.h"
#include "../Task2/Common.h"
#include "../Task2/Memory.h"

TEST_CASE("Function declaration")
{
	Memory memory;
	memory.AddVar("x");
	Function function("XPlusY", {"x"}, memory);
	CHECK(function.GetName() == "XPlusY");
}

SCENARIO("Function without operations can return value")
{
	GIVEN("Function named XPlusY and with operand 10")
	{
		Memory memory;
		memory.AddVar("x");
		memory.ChangeVarValue("x", 10);
		
		Function function("funcName", {"x"}, memory);
		CHECK(function.GetName() == "funcName");
		CHECK(IsEquals(function.GetValue(), 10));

		WHEN("Value of the variable changes")
		{
			memory.ChangeVarValue("x", 5);

			THEN("Value of the function changes too")
			{
				CHECK(IsEquals(function.GetValue(), 5));
			}
		}
	}
}
 
SCENARIO("Function can perform a simple arithmetic operation")
{
	GIVEN("Function that additing to vars")
	{
		Memory memory;
		memory.AddVar("x");
		memory.AddVar("y");
		Function function("XPlusY", { "x", "y", "+" }, memory);

		WHEN("I set value to vars")
		{
			memory.ChangeVarValue("x", 1);
			memory.ChangeVarValue("y", 2);

			THEN("Function can return sum of this vars")
			{
				CHECK(IsEquals(function.GetValue(), 3));
			}

			AND_WHEN("I change value of one variable")
			{
				memory.ChangeVarValue("x", 10);

				THEN("Functions value changes too")
				{
					CHECK(function.GetValue() == 12);
				}
			}
		}
	}
}