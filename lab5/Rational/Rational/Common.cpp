#include "Common.h"
#include <cmath>

bool IsEquals(double leftValue, double rightValue)
{
	return abs(leftValue - rightValue) <= 1e-7;
}