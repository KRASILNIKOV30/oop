#include "Calculator.h"
#include <algorithm>
#include <iterator>

std::vector<Var> Calculator::GetVars() const
{
	return m_vars;
}

std::vector<Function> Calculator::GetFunctions() const
{
	return m_functions;
}

std::optional<Var> Calculator::FindVar(std::string name) const
{
	auto result = std::find_if(begin(m_vars), end(m_vars), [name](Var var) { return var.GetName() == name; });
	if (result == end(m_vars))
	{
		return std::nullopt;
	}

	return *result;
}

std::optional<Function> Calculator::FindFunction(std::string name) const
{
	auto result = std::find_if(begin(m_functions), end(m_functions), [name](Function fn) { return fn.GetName() == name; });
	if (result == end(m_functions))
	{
		return std::nullopt;
	}

	return *result;
}

bool Calculator::DefineVar(std::string name)
{
	Var var(name);
	m_vars.push_back(var);
	return true;
}

bool Calculator::DefineFunction
(
	std::string name, 
	std::string leftOperandName,
	std::optional<Operation> operation,
	std::optional<std::string> rightOperandName
)
{
	std::optional<Var> leftOperand = FindVar(leftOperandName);
	if (!leftOperand.has_value())
	{
		return false;
	}
	Lexeme leftOperandLex(leftOperand.value());
	std::vector<Lexeme> lexemes = { leftOperandLex };
	Function function(name, lexemes);
	m_functions.push_back(function);
	return true;
}
