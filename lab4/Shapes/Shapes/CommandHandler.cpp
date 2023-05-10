#include "CommandHandler.h"
#include <sstream>
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "Common.h"


CommandHandler::CommandHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "rectangle", bind(&CommandHandler::AddRectangle, this, std::placeholders::_1) },
			{ "line", bind(&CommandHandler::AddLine, this, std::placeholders::_1) },
			{ "circle", bind(&CommandHandler::AddCircle, this, std::placeholders::_1) },
			{ "triangle", bind(&CommandHandler::AddTriangle, this, std::placeholders::_1) },
		})
{
}

bool CommandHandler::HandleCommand()
{
	std::string command;
	m_input >> command;
	std::istringstream strm(command);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

void CommandHandler::PrintResult()
{
	if (m_shapes.empty())
	{
		m_output << "Shapes not entered" << std::endl;
		return;
	}
	m_output << "Shape with max area:" << std::endl;
	PrintShape(GetMaxAreaShape());
	m_output << std::endl << "Shape with min perimeter:" << std::endl;
	PrintShape(GetMinPerimeterShape());
}


IShape& CommandHandler::GetMaxAreaShape()
{
	return *m_shapes[0];
}

IShape& CommandHandler::GetMinPerimeterShape()
{
	return *m_shapes[0];
}

void CommandHandler::PrintShape(IShape& shape) const
{
	m_output << shape.ToString() << std::endl;
	m_output << "area: " << shape.GetArea() << std::endl;
	m_output << "perimeter: " << shape.GetPerimeter() << std::endl;
}

bool CommandHandler::AddRectangle(std::istream& args)
{
	double x;
	double y;
	double width;
	double height;
	std::string fillColorStr;
	std::string outlineColorStr;
	if (!(m_input >> x && m_input >> y && m_input >> width && m_input >> height && m_input >> fillColorStr && m_input >> outlineColorStr))
	{
		return false;
	}
	uint32_t fillColor;
	uint32_t outlineColor;
	if (!(StringToUint32(fillColorStr, fillColor) && StringToUint32(outlineColorStr, outlineColor)))
	{
		return false;
	}
	m_shapes.push_back(new CRectangle(CPoint({ x, y }), width, height, fillColor, outlineColor));

	return true;
}

bool CommandHandler::AddLine(std::istream& args)
{
	double startX;
	double startY;
	double endX;
	double endY;
	std::string colorStr;
	if (!(m_input >> startX && m_input >> startY && m_input >> endX && m_input >> endY && m_input >> colorStr))
	{
		return false;
	}
	uint32_t color;
	if (!StringToUint32(colorStr, color))
	{
		return false;
	}
	m_shapes.push_back(new CLineSegment(CPoint({ startX, startY }), CPoint({ endX, endY }), color));

	return true;
}

bool CommandHandler::AddCircle(std::istream& args)
{
	double x;
	double y;
	double radius;
	std::string fillColorStr;
	std::string outlineColorStr;
	if (!(m_input >> x && m_input >> y && m_input >> radius && m_input >> fillColorStr && m_input >> outlineColorStr))
	{
		return false;
	}
	uint32_t fillColor;
	uint32_t outlineColor;
	if (!(StringToUint32(fillColorStr, fillColor) && StringToUint32(outlineColorStr, outlineColor)))
	{
		return false;
	}
	m_shapes.push_back(new CCircle(CPoint({ x, y }), radius, fillColor, outlineColor));

	return true;
}

bool CommandHandler::AddTriangle(std::istream& args)
{
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	std::string fillColorStr;
	std::string outlineColorStr;
	if (!(m_input >> x1 && m_input >> y1 && m_input >> x2 && m_input >> y2 && m_input >> x3 && m_input >> y3 && m_input >> fillColorStr && m_input >> outlineColorStr))
	{
		return false;
	}
	uint32_t fillColor;
	uint32_t outlineColor;
	if (!(StringToUint32(fillColorStr, fillColor) && StringToUint32(outlineColorStr, outlineColor)))
	{
		return false;
	}
	m_shapes.push_back(new CTriangle(CPoint({ x1, y1 }), CPoint({ x2, y2 }), CPoint({ x3, y3 }), fillColor, outlineColor));

	return true;
}

