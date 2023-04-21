#include "Calculator.h"
#include <algorithm>
#include <iterator>

VarsVector Calculator::GetVars() const
{
	return m_memory.GetVars();
}

FunctionsVector Calculator::GetFunctions() const
{
	return m_functions;
}

OptionalVar Calculator::FindVar(std::string name) const
{
	return m_memory.FindVar(name);
}

OptionalFunction Calculator::FindFunction(std::string name) const
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
	m_memory.AddVar(name);
	return true;
}

bool Calculator::DefineFunction(std::string name, std::string leftOperandName)
{
	Function function(name, { leftOperandName }, m_memory);
	m_functions.push_back(function);
	return true;
}

bool Calculator::DefineFunction(
	std::string name,
	std::string leftOperandName, 
	std::string operation,
	std::string rightOperandName
)
{
	return false;
}

bool Calculator::ChangeVarValue(std::string varName, double value)
{
	return m_memory.ChangeVarValue(varName, value);
}
