#include "../../../external/catch2/catch.hpp"
#include "../Task2/Var.h"
#include "Common.h"

SCENARIO("Variable declaration")
{
	GIVEN("Variable")
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
	GIVEN("Variable")
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

SCENARIO("Observer tests")
{
	GIVEN("Variable, notifying counter and two observers")
	{
		Var x;
		int counter = 0;
		Observer observer1 = [&]() { ++counter; };
		Observer observer2 = [&]() { ++counter; };

		WHEN("Register both observers and change var value")
		{
			x.RegisterObserver(observer1);
			x.RegisterObserver(observer2);
			x.SetValue(0);

			THEN("Both observers are notified")
			{
				CHECK(counter == 2);
			}
		}

		WHEN("Register only one observer and change var value")
		{
			x.RegisterObserver(observer1);
			x.SetValue(10);

			THEN("Only one observer is notified")
			{
				CHECK(counter == 1);
			}

			WHEN("Set the same value again")
			{
				x.SetValue(10);

				THEN("Observer is not notified again")
				{
					CHECK(counter == 1);
				}
			}
		}

		WHEN("Register both observers and remove one")
		{
			x.RegisterObserver(observer1);
			auto token = x.RegisterObserver(observer2);
			x.RemoveObserver(token);
			x.SetValue(0);

			THEN("Only one observer is notified")
			{
				CHECK(counter == 1);
			}
		}
	}
}