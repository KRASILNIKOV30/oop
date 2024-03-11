#include "../../../external/catch2/catch.hpp"
#include "../Task2/Var.h"
#include "Common.h"

SCENARIO("Variable declaration")
{
	GIVEN("Variable named x")
	{
		Var var;

		THEN("Recently declared variable must have a name and must have NAN value")
		{
			CHECK(isnan(var.GetValue()));
		}	
	}
}

SCENARIO("Assign a value to a variable")
{
	GIVEN("Variable named x")
	{
		Var var;

		WHEN("Assigning a value to a variable")
		{
			var.SetValue(10);

			THEN("Variable must have assigned value")
			{
				CHECK(IsEquals(var.GetValue(), 10));
			}
		}

		WHEN("Reassigning a value to a variable")
		{
			var.SetValue(10);
			var.SetValue(5);

			THEN("Variable must have reassigned value")
			{
				CHECK(IsEquals(var.GetValue(), 5));
			}
		}
	}
}