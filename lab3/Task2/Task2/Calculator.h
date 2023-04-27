#pragma once
#include "Var.h"
#include "Function.h"
#include "Common.h"
#include "Memory.h"
#include <vector>
#include <string>
#include <optional>
#include <list>

using FunctionsVector = std::vector<Function>;
using OptionalFunction = std::optional<Function>;

class Calculator
{
public:
	bool DefineVar(std::string name);
	bool DefineFunction(std::string name, std::string leftOperandName);
	bool DefineFunction
	(
		std::string name,
		std::string leftOperandName,
		std::string operation,
		std::string rightOperandName
	);
	bool ChangeVarValue(std::string varName, double value);
	VarsVector GetVars() const;
	FunctionsVector GetFunctions() const;
	OptionalVar FindVar(std::string name) const;
	OptionalFunction FindFunction(std::string name) const;

private:
	Memory m_memory;
	FunctionsVector m_functions;
	bool IsFunction(std::string name) const;
	bool IsVar(std::string name) const;
	bool AddLexemes(std::vector<std::string>& lexemes, std::string name) const;
	void InsertFunction(Function& fn);
	bool IsIdentifierAlreadyInUse(std::string name) const;
};