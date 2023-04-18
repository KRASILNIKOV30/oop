#include "Function.h"

Function::Function
(
	std::string name,
	double leftOperand,
	std::optional<Operations> operation,
	std::optional<double> rightOperand
)
	: m_name(name)
	, m_leftOperand(leftOperand)
{}

std::string Function::GetName() const
{
	return m_name;
}

