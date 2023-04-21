#include "../../../external/catch2/catch.hpp"
#include "../Task2/Function.h"
#include "../Task2/Var.h"
#include "../Task2/Common.h"
#include "../Task2/Lexeme.h"
#include "../Task2/Memory.h"

//TEST_CASE("Function declaration")
//{
//	Memory memory;
//	Var x("x");
//	memory.AddVar(x);
//	Function function("XPlusY", {"x"}, memory);
//	CHECK(function.GetName() == "XPlusY");
//}
//
//SCENARIO("Function without operations can return value")
//{
//	GIVEN("Function named XPlusY and with operand 10")
//	{
//		Memory memory;
//		Var x("x");
//		memory.AddVar(x);
//		x.SetValue(10.0);
//		
//		Function function("funcName", {"x"}, memory);
//		CHECK(function.GetName() == "funcName");
//		CHECK(function.GetValue() == 10.0);
//
//		WHEN("Value of the variable changes")
//		{
//			x.SetValue(5.0);
//
//			THEN("Value of the function changes too")
//			{
//				CHECK(function.GetValue() == 5.0);
//			}
//		}
//	}
//}
 
//SCENARIO("Function can perform a simple arithmetic operation")
//{
//	GIVEN("Function that additing to vars")
//	{
//		Memory memory;
//		Var x("x");
//		Var y("y");
//		memory.AddVar(x);
//		memory.AddVar(y);
//		Function function("XPlusY", { "x", "y", "+" }, memory);
//
//		WHEN("I set value to vars")
//		{
//			x.SetValue(1);
//			y.SetValue(2);
//
//			THEN("Function can return sum of this vars")
//			{
//				CHECK(function.GetValue() == 3);
//			}
//
//			AND_WHEN("I change value of one variable")
//			{
//				x.SetValue(10);
//
//				THEN("Functions value changes too")
//				{
//					CHECK(function.GetValue() == 12);
//				}
//			}
//		}
//	}
//}