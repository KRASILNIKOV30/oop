#include "Var.h"

Var::Var(std::string name)
	: m_name(name)
{}

std::string Var::GetName() const
{
	return m_name;
}

double Var::GetValue() const
{
	return m_value;
}

void Var::SetValue(double value)
{
	m_value = value;
}