#include "Lexeme.h"

Lexeme::Lexeme(Operation operation)
	: m_operation(operation)
	, m_var(*new Var)
{}

Lexeme::Lexeme(LexemeVarType var)
	: m_var(var)
{}

bool Lexeme::IsOperation() const
{
	return m_operation != Operation::NotOperation;
}

Var Lexeme::GetVar() const
{
	return m_var;
}

Operation Lexeme::GetOperation() const
{
	return m_operation;
}