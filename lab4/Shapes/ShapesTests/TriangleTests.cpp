#include "../Shapes/CTriangle.h"
#include "../../../external/catch2/catch.hpp"
#include "../Shapes/Common.h"

namespace
{
	const uint32_t fillColor = 16777215;
	const uint32_t outlineColor = 15;
	const CPoint vertex1 = { -3, 0 };
	const CPoint vertex2 = { 3, 0 };
	const CPoint vertex3 = { 0, 4 };
	const double expectedPerimeter = 16;
	const double expectedArea = 12;
}

struct TriangleFixture
{
	CTriangle triangle;
	fakeit::Mock<ICanvas> mockCanvas;
	std::stringstream output = std::stringstream();

	TriangleFixture()
		: triangle(CTriangle(vertex1, vertex2, vertex3, fillColor, outlineColor))
	{
		DefineMockCanvasBehavior(mockCanvas, output);
	}
};

TEST_CASE_METHOD(TriangleFixture, "triangle is a solid shape")
{
	CHECK(static_cast<const ISolidShape*>(&triangle));
}

TEST_CASE_METHOD(TriangleFixture, "triangle has three vertexes")
{
	CPoint point1 = triangle.GetVertex1();
	CPoint point2 = triangle.GetVertex2();
	CPoint point3 = triangle.GetVertex3();

	CHECK(point1.x == vertex1.x);
	CHECK(point1.y == vertex1.y);

	CHECK(point2.x == vertex2.x);
	CHECK(point2.y == vertex2.y);

	CHECK(point3.x == vertex3.x);
	CHECK(point3.y == vertex3.y);
}

TEST_CASE_METHOD(TriangleFixture, "triangle has an area")
{
	CHECK(IsEquals(triangle.GetArea(), expectedArea));
}

TEST_CASE_METHOD(TriangleFixture, "triangle has a perimeter")
{
	CHECK(IsEquals(triangle.GetPerimeter(), expectedPerimeter));
}

TEST_CASE_METHOD(TriangleFixture, "triangle has fill color")
{
	CHECK(triangle.GetFillColor() == fillColor);
}

TEST_CASE_METHOD(TriangleFixture, "triangle has outline color")
{
	CHECK(triangle.GetOutlineColor() == outlineColor);
}

TEST_CASE_METHOD(TriangleFixture, "triangle has info")
{
	CHECK(triangle.ToString() == std::format("triangle {} {} {} {} {} {} ffffff 00000f",
		vertex1.x,
		vertex1.y,
		vertex2.x,
		vertex2.y,
		vertex3.x,
		vertex3.y
	));
}

TEST_CASE_METHOD(TriangleFixture, "Triangle can be drawn")
{
	std::string expectedOutput;
	expectedOutput.append
	(
		std::format("Fill polygon with color {} in vertexes: ({}, {}) ({}, {}) ({}, {})\n",
			fillColor,
			vertex1.x,
			vertex1.y,
			vertex2.x,
			vertex2.y,
			vertex3.x,
			vertex3.y
		)
	);
	expectedOutput.append
	(
		std::format("Drawing line with color {} from ({}, {}) to ({}, {})\n",
			outlineColor,
			vertex1.x,
			vertex1.y,
			vertex2.x,
			vertex2.y
		)
	);
	expectedOutput.append
	(
		std::format("Drawing line with color {} from ({}, {}) to ({}, {})\n",
			outlineColor,
			vertex2.x,
			vertex2.y,
			vertex3.x,
			vertex3.y
		)
	);
	expectedOutput.append
	(
		std::format("Drawing line with color {} from ({}, {}) to ({}, {})\n",
			outlineColor,
			vertex3.x,
			vertex3.y,
			vertex1.x,
			vertex1.y
		)
	);

	triangle.Draw(mockCanvas.get());
	CHECK(output.str() == expectedOutput);
}