#include "CommandHandler.h"
#include <sstream>
#include "CLineSegment.h"
#include "Common.h"


CommandHandler::CommandHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "rectangle", bind(&CommandHandler::AddRectangle, this, std::placeholders::_1) },
			{ "line", bind(&CommandHandler::AddLine, this, std::placeholders::_1) }
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
	return false;
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
