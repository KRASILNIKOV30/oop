#include "../../../external/catch2/catch.hpp"
#include "../Radix/Radix.h"
#include <iostream>

const std::string MAXINT_STR = "2147483647";
const std::string MORE_THAN_MAXINT_STR = "2147483648";

TEST_CASE("Radix positive tests")
{
	CHECK(Radix("10", "10", "5") == "5");
	CHECK(Radix("10", "10", "10") == "10");
	CHECK(Radix("10", "16", "10") == "A");
	CHECK(Radix("10", "36", "35") == "Z");
	CHECK(Radix("10", "2", "10") == "1010");
	CHECK(Radix("36", "10", "Z") == "35");
	CHECK(Radix("10", "16", "2147483647") == "7FFFFFFF");
	CHECK(Radix("32", "10",	"1VVVVVV") == "2147483647");
	CHECK(Radix("2", "10",	"1111111111111111111111111111111") == "2147483647");

}