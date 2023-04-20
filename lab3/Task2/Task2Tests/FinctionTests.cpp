#include "../../../external/catch2/catch.hpp"
#include "../Task2/Function.h"
#include "../Task2/Var.h"
#include "../Task2/Common.h"
#include "../Task2/Lexeme.h"

SCENARIO("Function declaration")
{
	GIVEN("Function named XPlusY")
	{
		std::vector<Lexeme> lexemes;
		Function function("XPlusY", lexemes);
		CHECK(function.GetName() == "XPlusY");
	}
}

SCENARIO("Function without operations can return value")
{
	GIVEN("Function named XPlusY and with operand 10")
	{
		Var var("x");
		var.SetValue(10.0);
		Lexeme lexeme(Operation::NotOperation, var);
		std::vector<Lexeme> lexemes = { lexeme };
		Function function("XPlusY", lexemes);
		CHECK(function.GetName() == "XPlusY");
		CHECK(function.GetValue() == 10.0);

		WHEN("Value of the variable changes")
		{
			var.SetValue(5.0);

			THEN("Value of the function changes too")
			{
				CHECK(function.GetValue() == 5.0);
			}
		}
	}
}

TEST_CASE("Function can perform a simple arithmetic operation")
{
	Var x("x");
	Var y("y");
	x.SetValue(1);
	y.SetValue(2);
	Lexeme leftLex(Operation::NotOperation, x);
	Lexeme rightLex(Operation::NotOperation, y);
	Lexeme operationLex(Operation::Addition);
	Function function("XPlusY", { leftLex, rightLex, operationLex });
	CHECK(function.GetValue() == 3.0);
}