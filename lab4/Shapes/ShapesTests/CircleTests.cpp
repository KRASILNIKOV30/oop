#include "../Shapes/CCircle.h"
#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Common.h"

namespace
{
	const uint32_t fillColor = 16777215;
	const uint32_t outlineColor = 15;
	const double radius = 30;
	const CPoint center = { 9, 14 };
	const double expectedPerimeter = 188.49;
	const double expectedArea = 2827.35;
}

struct CircleFixture
{
	CCircle circle;

	CircleFixture()
		: circle(CCircle(center, radius, fillColor, outlineColor))
	{}
};

TEST_CASE_METHOD(CircleFixture, "circle is a solid shape")
{
	CHECK(static_cast<const ISolidShape*>(&circle));
}

TEST_CASE_METHOD(CircleFixture, "circle has a center")
{
	CPoint point = circle.GetCenter();
	CHECK(point.x == center.x);
	CHECK(point.y == center.y);
}

TEST_CASE_METHOD(CircleFixture, "circle has an area")
{
	CHECK(IsEquals(circle.GetArea(), expectedArea));
}

TEST_CASE_METHOD(CircleFixture, "circle has a perimeter")
{
	CHECK(IsEquals(circle.GetPerimeter(), expectedPerimeter));
}

TEST_CASE_METHOD(CircleFixture, "circle has fill color")
{
	CHECK(circle.GetFillColor() == fillColor);
}

TEST_CASE_METHOD(CircleFixture, "circle has outline color")
{
	CHECK(circle.GetOutlineColor() == outlineColor);
}

TEST_CASE_METHOD(CircleFixture, "circle has info")
{
	CHECK(circle.ToString() == std::format("circle {} {} {} ffffff 00000f",
		center.x,
		center.y,
		radius
	));
}