#include "CommandHandler.h"


CommandHandler::CommandHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "rectangle", bind(&CommandHandler::AddRectangle, this, std::placeholders::_1) },
			{ "line", bind(&CommandHandler::AddLine, this, std::placeholders::_1) }
		})
{
}

bool CommandHandler::AddRectangle(std::istream& args)
{
	return false;
}

bool CommandHandler::AddLine(std::istream& args)
{
	return false;
}
