#include "Common.h"
#include <math.h>
#include <limits>

bool IsEquals(double leftValue, double rightValue)
{
	return abs(leftValue - rightValue) < std::numeric_limits<double>::epsilon();
}