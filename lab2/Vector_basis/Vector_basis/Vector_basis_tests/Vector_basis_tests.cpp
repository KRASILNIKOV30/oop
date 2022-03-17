// Vector_basis_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <catch2/catch.hpp>
#include "../Vector_basis/VectorHandler.h"

TEST_CASE("ParseFloatsToVector: empty string to input")
{
	std::vector<float> v;
	std::istringstream input("");
	REQUIRE(!ParseFloatsToVector(input, v));
}

TEST_CASE("ParseFloatsToVector: invalid input with not only numbers")
{
	std::vector<float> v;
	std::istringstream input("1 2 3 test");
	REQUIRE(!ParseFloatsToVector(input, v));
}

TEST_CASE("ParseFloatsToVector: correct input")
{
	std::vector<float> v;
	std::vector<float> vExpected = { 1.0, 2.5, 3 };
	std::istringstream input("1.0 2.5 3");
	REQUIRE(ParseFloatsToVector(input, v));
	REQUIRE(v == vExpected);
}

TEST_CASE("MultElementsByMin: vector with same elements")
{
	std::vector<float> v = {2.0, 2.0, 2.0};
	std::vector<float> vExpected = { 4, 4, 4 };
	MultElementsByMin(v);
	REQUIRE(v == vExpected);
}

TEST_CASE("MultElementsByMin: vector with different elements ")
{
	std::vector<float> v = { 2.0, 7, 2.5 };
	std::vector<float> vExpected = { 4, 14, 5 };
	MultElementsByMin(v);
	REQUIRE(v == vExpected);
}

TEST_CASE("MultElementsByMin: vector with 0 ")
{
	std::vector<float> v = { 2.0, 7, 0 };
	std::vector<float> vExpected = { 0, 0, 0 };
	MultElementsByMin(v);
	REQUIRE(v == vExpected);
}
