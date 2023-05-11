#include "../../../external/catch2/catch.hpp"
#include <sstream>
#include "../Shapes/CommandHandler.h"

struct CommandHandlerDependencies
{
	std::stringstream input;
	std::stringstream output;
};

struct CommandHandlerFixture : CommandHandlerDependencies
{
	CommandHandler commandHandler;

	CommandHandlerFixture()
		: commandHandler(input, output)
	{
	}

	void VerifyCommandHandling(const std::string& command)
	{
		output = std::stringstream();
		input = std::stringstream();
		CHECK(input << command);
		if (!commandHandler.HandleCommand())
		{
			output << "Error!" << std::endl;
		}
		CHECK(input.eof());
	}

	void VerifyResult(const std::string& expectedOutput = "")
	{
		commandHandler.PrintResult();
		CHECK(output.str() == expectedOutput);
	}
};

TEST_CASE_METHOD(CommandHandlerFixture, "Printing result without shapes")
{
	VerifyResult("Shapes not entered\n");
}

TEST_CASE_METHOD(CommandHandlerFixture, "Printing result with one line")
{
	VerifyCommandHandling("line 2 3.5 5.0 7.5 111111");
	VerifyResult("Shape with max area:\nline 2 3.5 5 7.5 111111\narea: 0\nperimeter: 5\n\nShape with min perimeter:\nline 2 3.5 5 7.5 111111\narea: 0\nperimeter: 5\n");
}

TEST_CASE_METHOD(CommandHandlerFixture, "Printind result with one rectangele")
{
	VerifyCommandHandling("rectangle 4 0 8 4 00f110 000000");
	VerifyResult("Shape with max area:\nrectangle 4 0 8 4 00f110 000000\narea: 32\nperimeter: 24\n\nShape with min perimeter:\nrectangle 4 0 8 4 00f110 000000\narea: 32\nperimeter: 24\n");
}

TEST_CASE_METHOD(CommandHandlerFixture, "Printind result with one circle")
{
	VerifyCommandHandling("circle -1 -2 3 00f110 000000");
	VerifyResult("Shape with max area:\ncircle -1 -2 3 00f110 000000\narea: 28.2735\nperimeter: 18.849\n\nShape with min perimeter:\ncircle -1 -2 3 00f110 000000\narea: 28.2735\nperimeter: 18.849\n");
}

TEST_CASE_METHOD(CommandHandlerFixture, "Printind result with one triangle")
{
	VerifyCommandHandling("triangle 0 0 0 4 3 0 00f110 000000");
	VerifyResult("Shape with max area:\ntriangle 0 0 0 4 3 0 00f110 000000\narea: 6\nperimeter: 12\n\nShape with min perimeter:\ntriangle 0 0 0 4 3 0 00f110 000000\narea: 6\nperimeter: 12\n");
}

TEST_CASE_METHOD(CommandHandlerFixture, "All shapes")
{
	VerifyCommandHandling("circle -1 -2 3 00f110 000000");
	VerifyCommandHandling("line 2 3.5 5.0 7.5 111111");
	VerifyCommandHandling("rectangle 4 0 8 4 00f110 000000");
	VerifyCommandHandling("triangle 0 0 0 4 3 0 00f110 000000");
	VerifyResult("Shape with max area:\nrectangle 4 0 8 4 00f110 000000\narea: 32\nperimeter: 24\n\nShape with min perimeter:\nline 2 3.5 5 7.5 111111\narea: 0\nperimeter: 5\n");
}