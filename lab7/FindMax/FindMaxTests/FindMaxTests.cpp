#include "../../../external/catch2/catch.hpp"
#include "../FindMax/FindMax.h"

TEST_CASE("Find max in empty array")
{
	std::vector<int> v;
	int max;
	CHECK_FALSE(FindMax(v, max, [](int a, int b) { return a < b;  }));
}

SCENARIO("Find max in array with one value")
{
	GIVEN("Array with ine value")
	{
		std::vector<int> v{ 5 };

		WHEN("Find max in array with one value")
		{
			int max;
			CHECK(FindMax(v, max, [](int a, int b) { return a < b;  }));

			THEN("Max is equal to value in array")
			{
				CHECK(max == 5);
			}
		}
	}
}

SCENARIO("Find max in array of sportsmen")
{
	GIVEN("Array of three sportsmen")
	{
		struct Sportsman
		{
			std::string name;
			int height;
			int weight;
		};
		std::vector<Sportsman> sportsmen
		{
			{ "Vasya", 175, 85 },
			{ "Ivan", 190, 80 },
			{ "Petya", 170, 65 }
		};

		WHEN("Find sportsman with max height")
		{
			Sportsman maxHeight;
			CHECK(FindMax(sportsmen, maxHeight, [](Sportsman a, Sportsman b) { return a.height < b.height; }));

			THEN("Sportsman with max height is Ivan")
			{
				CHECK(maxHeight.name == "Ivan");
			}
		}

		WHEN("Find sportsman with max weight")
		{
			Sportsman maxWeight;
			CHECK(FindMax(sportsmen, maxWeight, [](Sportsman a, Sportsman b) { return a.weight < b.weight; }));

			THEN("Sportsman with max weight is Vasya")
			{
				CHECK(maxWeight.name == "Vasya");
			}
		}

	}
}

TEST_CASE("Check commit-or-rollback behavior")
{
	std::vector<int> v{ 2, 5 };
	int max = 1;
	CHECK_THROWS(FindMax(v, max, [](int a, int b) { throw std::exception{ "" }; return true;  }));
	CHECK(max == 1);
}
