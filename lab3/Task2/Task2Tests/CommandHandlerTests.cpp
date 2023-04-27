#include "../../../external/catch2/catch.hpp"
#include <sstream>
#include "../Task2/CommandHandler.h"

struct CommandHandlerDependencies
{
	Calculator calc;
	std::stringstream input;
	std::stringstream output;
};

struct CommandHandlerFixture : CommandHandlerDependencies
{
	CommandHandler commandHandler;

	CommandHandlerFixture()
		: commandHandler(calc, input, output)
	{
	}

	void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput = "")
	{
		output = std::stringstream();
		input = std::stringstream();
		CHECK(input << command);
		if (!commandHandler.HandleCommand())
		{
			output << "Error!" << std::endl;
		}
		CHECK(input.eof());
		CHECK(output.str() == expectedOutput);
	}
};

SCENARIO_METHOD(CommandHandlerFixture, "Handle variable definition")
{
	VerifyCommandHandling("printvars", "");

	WHEN("I can define variable with var")
	{
		VerifyCommandHandling("var x", "");

		THEN("Calculator has one variable with nan value")
		{
			VerifyCommandHandling("print x", "nan\n");
		}
	}

	WHEN("I can define variable with let")
	{
		VerifyCommandHandling("let x=42", "");

		THEN("Calculator has one variable")
		{
			VerifyCommandHandling("print x", "42.00\n");
		}
	}
}

SCENARIO_METHOD(CommandHandlerFixture, "Change variables value")
{
	GIVEN("Two variables x and y")
	{
		VerifyCommandHandling("var y");
		VerifyCommandHandling("var x");
		

		WHEN("I change x variables value")
		{
			VerifyCommandHandling("let x=2.5", "");

			THEN("X variable has value, y has not, variables sorted")
			{
				VerifyCommandHandling("printvars", "x:2.50\ny:nan\n");
			}

			AND_WHEN("I assign x to y")
			{
				VerifyCommandHandling("let y=x", "");

				THEN("y equals to x")
				{
					VerifyCommandHandling("printvars", "x:2.50\ny:2.50\n");
				}

				AND_WHEN("I change x value")
				{
					VerifyCommandHandling("let x=3", "");

					THEN("Y value did not change")
					{
						VerifyCommandHandling("printvars", "x:3.00\ny:2.50\n");
					}
				}
			}
		}
	}
}

SCENARIO_METHOD(CommandHandlerFixture, "Handle function definition")
{
	VerifyCommandHandling("printfns", "");

	GIVEN("Two variables x and y")
	{
		VerifyCommandHandling("var x");
		VerifyCommandHandling("var y");

		WHEN("I define function depends on variable")
		{
			VerifyCommandHandling("fn Fn=x", "");

			THEN("Function is defined")
			{
				VerifyCommandHandling("print Fn", "nan\n");
			}
		}

		WHEN("I defined function depends on two variables")
		{
			VerifyCommandHandling("fn Fn=x+y", "");

			THEN("Function is defined")
			{
				VerifyCommandHandling("print Fn", "nan\n");
			}
		}
		
		WHEN("I defined function depends on another function")
		{
			VerifyCommandHandling("fn Fn=x+y", "");
			VerifyCommandHandling("fn FnPlusX=Fn+x", "");

			THEN("Function is defined")
			{
				VerifyCommandHandling("print FnPlusX", "nan\n");
			}
		}
	}
}

SCENARIO_METHOD(CommandHandlerFixture, "Change function value")
{
	GIVEN("Two variables x and y")
	{
		VerifyCommandHandling("var x");
		VerifyCommandHandling("var y");

		WHEN("I defined function depends on one var, on two vars and on another function")
		{
			VerifyCommandHandling("fn XPlusY=x+y", "");
			VerifyCommandHandling("fn XYAvg=XPlusY/y", "");
			VerifyCommandHandling("fn XFn=x", "");
			
			THEN("All functions has a nan value and functions sorted")
			{
				VerifyCommandHandling("printfns", "XFn:nan\nXPlusY:nan\nXYAvg:nan\n");
			}

			AND_WHEN("I initialize x")
			{
				VerifyCommandHandling("let x=9", "");

				THEN("Only one function has value")
				{
					VerifyCommandHandling("printfns", "XFn:9.00\nXPlusY:nan\nXYAvg:nan\n");
				}

				AND_WHEN("I initialize y")
				{
					VerifyCommandHandling("let y=2", "");

					THEN("All functions have value")
					{
						VerifyCommandHandling("printfns", "XFn:9.00\nXPlusY:11.00\nXYAvg:5.50\n");
					}
				}
			}
		}
	}
}

TEST_CASE_METHOD(CommandHandlerFixture, "Can not define variable with invalid identifier")
{
	VerifyCommandHandling("var 1var", "Error!\n");
	VerifyCommandHandling("let var*=42", "Error!\n");
	VerifyCommandHandling("printvars", "");
}

TEST_CASE_METHOD(CommandHandlerFixture, "Can not define function with invalid identifier")
{
	VerifyCommandHandling("var x", "");
	VerifyCommandHandling("fn 1fn=x", "Error!\n");
	VerifyCommandHandling("fn fn<fn=x", "Error!\n");
	VerifyCommandHandling("printfns", "");
}

TEST_CASE_METHOD(CommandHandlerFixture, "Can not define function with invalid syntax")
{
	VerifyCommandHandling("var x", "");
	VerifyCommandHandling("fn", "Error!\n");
	VerifyCommandHandling("fn =x", "Error!\n");
	VerifyCommandHandling("fn fn", "Error!\n");
	VerifyCommandHandling("fn fn=", "Error!\n");
	VerifyCommandHandling("fn fn=5", "Error!\n");
	VerifyCommandHandling("fn fn=x&x", "Error!\n");
	VerifyCommandHandling("printfns", "");
}

TEST_CASE_METHOD(CommandHandlerFixture, "Can not use one identifier twice")
{
	VerifyCommandHandling("var x", "");
	VerifyCommandHandling("fn y=x", "");
	VerifyCommandHandling("var y", "Error!\n");
	VerifyCommandHandling("fn x=x", "Error!\n");
}