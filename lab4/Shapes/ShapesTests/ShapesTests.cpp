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