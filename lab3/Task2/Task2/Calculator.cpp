#include "Calculator.h"

std::vector<Var> Calculator::GetVars() const
{
	return m_vars;
}

std::vector<Function> Calculator::GetFunctions() const
{
	return m_functions;
}

bool Calculator::DefineVar(std::string name)
{
	Var var(name);
	m_vars.push_back(var);
	return true;
}
