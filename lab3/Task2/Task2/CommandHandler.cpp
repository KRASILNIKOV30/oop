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
			{ "let", bind(&CommandHandler::LetVar, this, std::placeholders::_1) },
			{ "printfns", bind(&CommandHandler::PrintFns, this, std::placeholders::_1)},
			{ "fn", bind(&CommandHandler::DefineFn, this, std::placeholders::_1)},
			{ "print", bind(&CommandHandler::Print, this, std::placeholders::_1)},
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

bool CommandHandler::DefineFn(std::istream& args)
{
	std::string expression;
	m_input >> expression;
	std::string name;
	std::string leftOperand;
	std::string operation;
	std::string rightOperand;
	if (!ParseFnExpression(expression, name, leftOperand, operation, rightOperand))
	{
		return false;
	}
	return operation == "" 
		? m_calc.DefineFunction(name, leftOperand)
		: m_calc.DefineFunction(name, leftOperand, operation, rightOperand);
}

bool CommandHandler::LetVar(std::istream& args)
{
	std::string expression;
	m_input >> expression;
	std::string leftOperand;
	std::string rightOperand;
	ParseLetExpression(expression, leftOperand, rightOperand);
	auto var = m_calc.FindVar(rightOperand);
	if(var.has_value())
	{
		return m_calc.ChangeVarValue(leftOperand, var->GetValue());
	}
	try
	{
		return m_calc.ChangeVarValue(leftOperand, stod(rightOperand));
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool CommandHandler::Print(std::istream& args)
{
	std::string name;
	m_input >> name;
	auto fn = m_calc.FindFunction(name);
	auto var = m_calc.FindVar(name);
	if (fn.has_value())
	{
		m_output << fn->GetValue() << std::endl;
		return true;
	}
	if (var.has_value())
	{
		m_output << var->GetValue() << std::endl;
		return true;
	}

	return false;
}

bool CommandHandler::ParseLetExpression(std::string exp, std::string& leftOperand, std::string& rightOperand)
{
	const std::regex reg(R"(([\w]+)=([\w.]+))");
	std::smatch matchResutl;
	if (!std::regex_match(exp, matchResutl, reg)) 
	{
		return false;
	}
	leftOperand = matchResutl[1];
	rightOperand = matchResutl[2];
	return true;
}

bool CommandHandler::ParseFnExpression
(
	std::string exp, 
	std::string& name, 
	std::string& leftOperand,
	std::string& operation, 
	std::string& rightOperand
)
{
	const std::regex reg(R"(([\w]+)=([\w]+)(([\+\-\*\/])([\w]+))?)");
	std::smatch matchResult;
	if (!std::regex_match(exp, matchResult, reg))
	{
		return false;
	}
	name = matchResult[1];
	leftOperand = matchResult[2];
	operation = matchResult[4];
	rightOperand = matchResult[5];
	return true;
}

bool CommandHandler::PrintVars(std::istream& args)
{
	VarsVector vars = m_calc.GetVars();
	std::sort(vars.begin(), vars.end());
	m_output.setf(std::ios::fixed);
	m_output.precision(2);
	for (auto& var : vars)
	{
		m_output << var.GetName() << ":" << var.GetValue() << std::endl;
	}
	return true;
}

bool CompareByNames(const Function& a, const Function& b)
{
	return a.GetName() < b.GetName();
}

bool CommandHandler::PrintFns(std::istream& args)
{
	FunctionsVector fns = m_calc.GetFunctions();
	m_output.setf(std::ios::fixed);
	m_output.precision(2);
	for (auto& fn : fns)
	{
		m_output << fn.GetName() << ":" << fn.GetValue() << std::endl;
	}
	return true;
}
