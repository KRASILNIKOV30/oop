#include "../Shapes/CRectangle.h"
#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Common.h"

namespace
{
	const uint32_t fillColor = 16777215;
	const uint32_t outlineColor = 15;
	const double width = 30;
	const double height = 12.3;
	const CPoint leftTopPoint = { 0, 0.5 };
	const CPoint rightBottomPoint = { 0 + width, 0.5 + height };
	const double expectedPerimeter = 84.6;
	const double expectedArea = 369;
}

struct RectangleFixture
{
	CRectangle rect;

	RectangleFixture()
		: rect(CRectangle(leftTopPoint, width, height, fillColor, outlineColor))
	{}
};

TEST_CASE_METHOD(RectangleFixture, "Rect is a solid shape")
{
	CHECK(static_cast<const ISolidShape*>(&rect));
}

TEST_CASE_METHOD(RectangleFixture, "Rect has a left top point")
{
	CPoint point = rect.GetLeftTop();
	CHECK(point.x == leftTopPoint.x);
	CHECK(point.y == leftTopPoint.y);
}

TEST_CASE_METHOD(RectangleFixture, "Rect has a end point")
{
	CPoint point = rect.GetRightBottom();
	CHECK(point.x == rightBottomPoint.x);
	CHECK(point.y == rightBottomPoint.y);
}

TEST_CASE_METHOD(RectangleFixture, "Rect has an area")
{
	CHECK(IsEquals(rect.GetArea(), expectedArea));
}

TEST_CASE_METHOD(RectangleFixture, "Rect has a perimeter")
{
	CHECK(IsEquals(rect.GetPerimeter(), expectedPerimeter));
}

TEST_CASE_METHOD(RectangleFixture, "Rect has fill color")
{
	CHECK(rect.GetFillColor() == fillColor);
}

TEST_CASE_METHOD(RectangleFixture, "Rect has outline color")
{
	CHECK(rect.GetOutlineColor() == outlineColor);
}

TEST_CASE_METHOD(RectangleFixture, "Rect has info")
{
	CHECK(rect.ToString() == std::format("rectangle {} {} {} {} ffffff 00000f", 
		leftTopPoint.x,
		leftTopPoint.y,
		width,
		height
	));
}