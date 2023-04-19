#pragma once
#include "Var.h"
#include "Common.h"
#include <optional>
#include <memory>

using LexemeVarType = Var&;

class Lexeme
{
public:
	Lexeme(Operation operation, LexemeVarType var = *new Var);
	Var GetVar() const;
	Operation GetOperation() const;
	bool IsOperation() const;

private:
	LexemeVarType m_var;
	std::optional<Operation> m_operation;
	bool m_isOperation = true;
};
