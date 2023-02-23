#include "../TextAnalysis/TextAnalysis.h"
#include "../../../external/catch2/catch.hpp"
#include <iostream>
#include <sstream>

namespace 
{
	void TestTextAnalysis(std::string input, std::string expectation)
	{
		std::stringstream buffer;
		std::streambuf* coutBuffer = std::cout.rdbuf(buffer.rdbuf());
		std::istringstream inputStream(input);
		TextAnalysis(inputStream);
		std::string result = buffer.str();
		REQUIRE(result == expectation);
		std::cout.rdbuf(coutBuffer);
	}
}


TEST_CASE("unique words")
{
	TestTextAnalysis("hello	world ", "hello 1\nworld 1\n");
}

TEST_CASE("only repetitions")
{
	TestTextAnalysis("	Hello hello\n	 HELLO", "hello 3\n");
}

TEST_CASE("empty input")
{
	TestTextAnalysis("", "");
}


