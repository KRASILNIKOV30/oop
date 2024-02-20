#include "../../../external/catch2/catch.hpp"
#include "../Radix/Radix.h"
#include <iostream>

TEST_CASE("Radix positive tests")
{
	CHECK(ChangeNotation(10, 10, "5") == "5");
	CHECK(ChangeNotation(10, 10, "10") == "10");
	CHECK(ChangeNotation(10, 16, "10") == "A");
	CHECK(ChangeNotation(10, 36, "35") == "Z");
	CHECK(ChangeNotation(10, 2, "10") == "1010");
	CHECK(ChangeNotation(36, 10, "Z") == "35");
	CHECK(ChangeNotation(10, 16, "2147483647") == "7FFFFFFF");
	CHECK(ChangeNotation(32, 10, "1VVVVVV") == "2147483647");
	CHECK(ChangeNotation(2, 10, "1111111111111111111111111111111") == "2147483647");
	//CHECK(ChangeNotation(2, 36, "0") == "0");
	CHECK(ChangeNotation(2, 10, "-101") == "-5");
	CHECK(ChangeNotation(32, 10, "-2000000") == "-2147483648");
}

TEST_CASE("Radix negative tests")
{
	CHECK_THROWS_AS(ChangeNotation(10, 10, "2147483648"), std::invalid_argument);
	CHECK_THROWS_AS(ChangeNotation(10, 10, "-2147483649"), std::invalid_argument);
	CHECK_THROWS_AS(ChangeNotation(1, 10, "0"), std::invalid_argument);
	CHECK_THROWS_AS(ChangeNotation(10, 37, "0"), std::invalid_argument);

}