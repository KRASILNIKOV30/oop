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
		CHECK(commandHandler.HandleCommand());
		CHECK(input.eof());
		CHECK(output.str() == expectedOutput);
	}
};

SCENARIO_METHOD(CommandHandlerFixture, "Handle variable definition")
{
	VerifyCommandHandling("printvars", "");

	WHEN("I define variable")
	{
		VerifyCommandHandling("var x", "");

		THEN("Calculator has one variable with nan value")
		{
			VerifyCommandHandling("printvars", "x:nan\n");
		}

		WHEN("I change variables value")
		{
			VerifyCommandHandling("let x=1");

			THEN("Variables value change")
			{
				VerifyCommandHandling("printvars", "x:1\n");
			}
		}
	}
}

SCENARIO_METHOD(CommandHandlerFixture, "Change variables value")
{
	GIVEN("Two variables x and y")
	{
		VerifyCommandHandling("var x");
		VerifyCommandHandling("var y");

		WHEN("I change x variables value")
		{
			VerifyCommandHandling("let x=2.5", "");

			THEN("X variable has value, y has not, variables sorted")
			{
				VerifyCommandHandling("printvars", "x:2.5\ny:nan\n");
			}
		}
	}
}