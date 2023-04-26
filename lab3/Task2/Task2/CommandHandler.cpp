#include "CommandHandler.h"
#include <sstream>
#include <regex>

CommandHandler::CommandHandler(Calculator& calc, std::istream& input, std::ostream& output)
	: m_calc(calc)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "printvars", bind(&CommandHandler::PrintVars, this, std::placeholders::_1) },
			{ "var", bind(&CommandHandler::DefineVar, this, std::placeholders::_1) },
			{ "let", bind(&CommandHandler::LetVar, this, std::placeholders::_1) }
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

bool CommandHandler::DefineVar(std::istream& args)
{
	std::string name;
	m_input >> name;
	return m_calc.DefineVar(name);
}

bool CommandHandler::LetVar(std::istream& args)
{
	std::string expression;
	m_input >> expression;
	std::string leftOperand;
	std::string rightOperand;
	ParseLetExpression(expression, leftOperand, rightOperand);
	m_calc.ChangeVarValue(leftOperand, std::stoi(rightOperand));
	return true;
}

bool CommandHandler::ParseLetExpression(std::string exp, std::string& leftOperand, std::string& rightOperand)
{
	const std::regex reg(R"(([\w]+)=([\w.]+))");
	std::smatch matchResutl;
	if (!std::regex_match(exp, matchResutl, reg)) {
		return false;
	}
	leftOperand = matchResutl[1];
	rightOperand = matchResutl[2];
	return false;
}

bool CommandHandler::PrintVars(std::istream& args)
{
	VarsVector vars = m_calc.GetVars();
	for (auto& var : vars)
	{
		m_output << var.GetName() << ":" << var.GetValue() << std::endl;
	}
	return true;
}
