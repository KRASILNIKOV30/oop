#include "Common.h"
#include <math.h>
#include <limits>
#include <string>

bool IsEquals(double leftValue, double rightValue)
{
	return abs(leftValue - rightValue) < std::numeric_limits<double>::epsilon();
}

bool IsOperation(std::string str)
{
	return str == "+" || str == "-" || str == "*" || str == "/";
}