#pragma once
#include "Var.h"
#include "Function.h"
#include "Common.h"
#include "Memory.h"
#include <vector>
#include <string>
#include <optional>
#include <list>
#include <memory>

using FunctionsVector = std::vector<Function>;
using OptionalFunction = std::optional<Function>;
using VarsVector = std::vector<Var>;

class Calculator
{
public:
	bool DefineVar(std::string const& name);
	bool DefineFunction(std::string const& name, std::string leftOperandName);
	bool DefineFunction
	(
		std::string const& name,
		std::string const& leftOperandName,
		std::string const& operation,
		std::string const& rightOperandName
	);
	bool ChangeVarValue(std::string const& varName, double value);
	VarsVector GetVars() const;
	FunctionsVector GetFunctions() const;
	//Можно передавать имя по ссылке (Исправлено)
	OptionalVar FindVar(std::string const& name) const;
	//Ускорить поиск (map)
	OptionalFunction FindFunction(std::string const& name) const;

private:
	std::shared_ptr<Memory> m_memory = std::make_shared<Memory>();
	FunctionsVector m_functions;
	bool IsFunction(std::string const& name) const;
	bool IsVar(std::string const& name) const;
	bool AddLexemes(std::vector<std::string>& lexemes, std::string name) const;
	void InsertFunction(Function& fn);
	bool IsIdentifierAlreadyInUse(std::string const& name) const;
};