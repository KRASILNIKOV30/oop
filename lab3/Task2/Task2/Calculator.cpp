#include "Calculator.h"
#include <algorithm>
#include <iterator>

Var Calculator::GetVars() const
{
	Var var = m_memory.GetVars()[0];
	return var;
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
	Var var(name);
	m_memory.AddVar(var);
	return true;
}

bool Calculator::DefineFunction(std::string name, std::string leftOperandName)
{
	Function function(name, { leftOperandName }, m_memory);
	m_functions.push_back(function);
	return false;
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
