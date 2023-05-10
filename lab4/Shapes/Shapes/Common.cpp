#pragma once
#include "Common.h"
#include <math.h>
#include <limits>
#include <sstream>
#include <iomanip>

bool IsEquals(double leftValue, double rightValue)
{
	return abs(leftValue - rightValue) <= std::numeric_limits<double>::epsilon();
}

bool StringToUint32(std::string const& str, uint32_t& uint32)
{
	int i;
	try
	{
		i = std::stoi(str, 0, COLOR_RADIX);
	}
	catch (const std::exception&)
	{
		return false;
	}
	if (i < 0 || i > UINT32_MAX)
	{
		return false;
	}
	uint32 = i;
	return true;
}

std::string GetHexStrFromUint32(uint32_t const& uint32, int len)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(len) << std::hex << uint32;
	return stream.str();
}