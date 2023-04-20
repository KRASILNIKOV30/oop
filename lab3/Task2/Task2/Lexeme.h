#pragma once
#include "Var.h"
#include "Common.h"
#include <optional>
#include <memory>

using LexemeVarType = Var&;

class Lexeme
{
public:
	Lexeme(Operation operation);
	Lexeme(LexemeVarType var);
	Lexeme(Lexeme const& lexeme);
	Var& GetVar() const;
	Operation GetOperation() const;
	bool IsOperation() const;

private:
	LexemeVarType m_var;
	Operation m_operation = Operation::NotOperation;
	bool m_isOperation = false;	
};