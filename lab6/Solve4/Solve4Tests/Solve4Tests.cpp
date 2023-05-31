#include "../../../external/catch2/catch.hpp"
#include "../Solve4/Solve4.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include "../Solve4/Common.h"

namespace
{
    bool AreArraysEqual(double arr1[], double arr2[], int len)
    {
        std::sort(arr1, arr1 + len);
        std::sort(arr2, arr2 + len);

        for (int i = 0; i < len; i++)
        {
            if (!AreDoublesEqual(arr1[i], arr2[i]))
            {
                return false;
            }
        }
            
        return true;
    }
}

TEST_CASE("Zero higher coefficient")
{
	CHECK_THROWS_AS(Solve4(0, 3, 2, 1, 3), std::invalid_argument);
}

TEST_CASE("Equations with 4 real roots")
{
    auto solution = Solve4(1, -2, -13, 14, 24);;
    double expRoots[4] = {-1, 2, -3, 4};
    CHECK(solution.numRoots == 4);
    CHECK(AreArraysEqual(solution.roots, expRoots, 4));
}

TEST_CASE("Equations with 2 real roots")
{
    auto solution = Solve4(1, -1, -1, -1, -2);;
    double expRoots[2] = { -1, 2 };
    CHECK(solution.numRoots == 2);
    CHECK(AreArraysEqual(solution.roots, expRoots, 2));
}

TEST_CASE("Equations without real roots")
{
    CHECK_THROWS_AS(Solve4(1, 0, 2, 0, 1), std::domain_error);
}