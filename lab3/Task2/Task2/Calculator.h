#pragma once
#include "Var.h"
#include "Function.h"
#include "Common.h"
#include <vector>
#include <string>
#include <optional>

class Calculator
{
public:
	bool DefineVar(std::string name);
	bool DefineFunction
	(
		std::string name,
		std::string leftOperandName,
		std::optional<Operation> operation = std::nullopt,
		std::optional<std::string> rightOperandName = std::nullopt
	);
	std::vector<Var> GetVars() const;
	std::vector<Function> GetFunctions() const;
	std::optional<Var> FindVar(std::string name) const;
	std::optional<Function> FindFunction(std::string name) const;

private:
	std::vector<Var> m_vars;
	std::vector<Function> m_functions;
};