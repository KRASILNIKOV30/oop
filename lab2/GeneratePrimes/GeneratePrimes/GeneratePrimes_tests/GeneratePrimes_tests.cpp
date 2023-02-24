#include "../GeneratePrimes/GeneratePrimeNumbersSet.h"
#include "../../../../external/catch2/catch.hpp"
#include <iostream>
#include <set>
#include <boost/timer.hpp>

namespace {
	std::set<int> expectedSet;
}

TEST_CASE("empty output") {
	expectedSet = {};
	REQUIRE(GeneratePrimeNumbersSet(1) == expectedSet);
}

TEST_CASE("only one prime number") {
	expectedSet = { 2 };
	REQUIRE(GeneratePrimeNumbersSet(2) == expectedSet);
}

TEST_CASE("primes lower than 30") {
	expectedSet = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	REQUIRE(GeneratePrimeNumbersSet(30) == expectedSet);
}

TEST_CASE("Performance test") {
	boost::timer t;
	t.restart();
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
	std::cout << "Perfomance test duration: " << t.elapsed() << std::endl;
}