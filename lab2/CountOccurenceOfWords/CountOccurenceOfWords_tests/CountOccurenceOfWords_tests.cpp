#include "../CountOccurenceOfWords/CountOccurenceOfWords.h"
#include "../../../external/catch2/catch.hpp"
#include <iostream>
#include <sstream>

namespace 
{
	void TestCountOccurenceOfWords(std::string input, std::string expectation)
	{
		std::stringstream buffer;
		std::streambuf* coutBuffer = std::cout.rdbuf(buffer.rdbuf());
		std::istringstream inputStream(input);
		CountOccurenceOfWords(inputStream);
		std::string result = buffer.str();
		REQUIRE(result == expectation);
		std::cout.rdbuf(coutBuffer);
	}
}


TEST_CASE("unique words")
{
	CountOccurenceOfWords("hello	world ", "hello 1\nworld 1\n");
}

TEST_CASE("only repetitions")
{
	CountOccurenceOfWords("	Hello hello\n	 HELLO", "hello 3\n");
}

TEST_CASE("empty input")
{
	CountOccurenceOfWords("", "");
}


