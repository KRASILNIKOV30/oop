#include "../../../external/catch2/catch.hpp"
#include "../Solve4/Solve4.h"
#include <iostream>
#include <iterator>
#include <algorithm>

namespace
{
    bool AreDoublesEqual(double leftValue, double rightValue)
    {
        return abs(leftValue - rightValue) <= 1e-7;
    }

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
    auto solution = Solve4(1, -10, 35, -50, 24);;
    double expRoots[4] = {1, 2, 3, 4};
    CHECK(solution.numRoots == 4);
    CHECK(sizeof(solution.roots) / sizeof(solution.roots)[0] == 4);
    CHECK(AreArraysEqual(solution.roots, expRoots, 4));
}