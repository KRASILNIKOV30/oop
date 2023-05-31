#include <algorithm>

bool AreDoublesEqual(double leftValue, double rightValue)
{
    return abs(leftValue - rightValue) <= 1e-3;
}