#pragma once
#include "Common.h"
#include <math.h>
#include <sstream>
#include <iomanip>

bool IsEquals(double leftValue, double rightValue)
{
	return abs(leftValue - rightValue) <= 1e-7;
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

double GetLineLength(CPoint start, CPoint end)
{
	//������������ std::hypot (����������)
	return std::hypot((end.x - start.x), (end.y - start.y));
}

void DefineMockCanvasBehavior(fakeit::Mock<ICanvas>& canvas, std::ostream& output)
{
	fakeit::When(Method(canvas, DrawLine)).AlwaysDo([&output](CPoint from, CPoint to, uint32_t color)
		{
			output << "Drawing line with color " << color << " from (" << from.x << ", " << from.y << ") to (" << to.x << ", " << to.y << ")";
		});
}

