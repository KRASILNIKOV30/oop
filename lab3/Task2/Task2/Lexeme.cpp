#include "Lexeme.h"

Lexeme::Lexeme(Operation operation, LexemeVarType var)
	: m_var(var)
	, m_operation(operation)
{
	if (operation == Operation::NotOperation)
	{
		m_isOperation = false;
	}
};

bool Lexeme::IsOperation() const
{
	return m_isOperation;
}

Var Lexeme::GetVar() const
{
	return m_var;
}

Operation Lexeme::GetOperation() const
{
	return m_operation.value();
}