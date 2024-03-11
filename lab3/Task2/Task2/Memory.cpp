#include "Memory.h"

bool Memory::AddVar(std::string const& name)
{
	Var var;
	m_vars.insert({ name, var });
	return true;
}

bool Memory::ChangeVarValue(std::string const& varName, double value)
{
	auto var = FindVar(varName);
	if (!var.has_value())
	{
		return false;
	}
	DeleteVar(varName);
	var->SetValue(value);
	m_vars.insert({ varName, var.value()});
	return true;
}

OptionalVar Memory::FindVar(std::string const& name) const
{
	auto result = m_vars.find(name);
	if (result == m_vars.end())
	{
		return std::nullopt;
	}

	return result->second;
}

VarsMap Memory::GetVars() const
{
	return m_vars;
}

void Memory::DeleteVar(std::string const& name)
{
	m_vars.erase(m_vars.find(name));
}
