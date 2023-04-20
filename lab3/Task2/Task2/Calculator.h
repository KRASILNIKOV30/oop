#pragma once
#include "Var.h"
#include "Function.h"
#include <vector>
#include <string>

class Calculator
{
public:
	bool DefineVar(std::string name);
	std::vector<Var> GetVars() const;
	std::vector<Function> GetFunctions() const;
private:
	std::vector<Var> m_vars;
	std::vector<Function> m_functions;
};