#include "../Shapes/CLineSegment.h"
#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Common.h"

namespace 
{
	const uint32_t color = 10;
	const CPoint startPoint = { 1, 3.3 };
	const CPoint endPoint = { 7, 11.3 };
	const double expectedPerimeter = 10;
	const double expectedArea = 0;
}

struct LineSegmentFixture
{
	CLineSegment line;
	
	LineSegmentFixture()
		: line(CLineSegment(startPoint, endPoint, color))
	{}
};

TEST_CASE_METHOD(LineSegmentFixture, "Line is a body")
{
	CHECK(static_cast<const Shape*>(&line));
}

TEST_CASE_METHOD(LineSegmentFixture, "Line has a start point")
{
	CPoint point = line.GetStartPoint();
	CHECK(point.x == startPoint.x);
	CHECK(point.y == startPoint.y);
}

TEST_CASE_METHOD(LineSegmentFixture, "Line has a end point")
{
	CPoint point = line.GetEndPoint();
	CHECK(point.x == endPoint.x);
	CHECK(point.y == endPoint.y);
}

TEST_CASE_METHOD(LineSegmentFixture, "Line has an area")
{
	CHECK(IsEquals(line.GetArea(), expectedArea));
}

TEST_CASE_METHOD(LineSegmentFixture, "Line has a perimeter")
{
	CHECK(IsEquals(line.GetPerimeter(), expectedPerimeter));
}

TEST_CASE_METHOD(LineSegmentFixture, "Line has a color")
{
	CHECK(line.GetOutlineColor() == color);
}

TEST_CASE_METHOD(LineSegmentFixture, "Line has info")
{
	CHECK(line.ToString() == std::format("line {} {} {} {} 00000a",
		startPoint.x,
		startPoint.y,
		endPoint.x,
		endPoint.y
	));
}