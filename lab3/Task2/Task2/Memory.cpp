#include "Memory.h"

bool Memory::AddVar(std::string name)
{
	Var var(name);
	InsertVar(var);
	return true;
}

bool Memory::ChangeVarValue(std::string varName, double value)
{
	auto var = FindVar(varName);
	if (!var.has_value())
	{
		return false;
	}
	DeleteVar(varName);
	var->SetValue(value);
	InsertVar(var.value());
	return true;
}

OptionalVar Memory::FindVar(std::string name) const
{
	auto result = std::find_if(begin(m_vars), end(m_vars), [name](Var var) { return var.GetName() == name; });
	if (result == end(m_vars))
	{
		return std::nullopt;
	}

	return *result;
}

VarsVector Memory::GetVars() const
{
	return m_vars;
}

void Memory::DeleteVar(std::string name)
{
	m_vars.erase(
		std::remove_if(m_vars.begin(), m_vars.end(),
			[name](const Var& var) {return var.GetName() == name; }),
		m_vars.end()
	);
}

void Memory::InsertVar(Var& var)
{
	if (m_vars.size() == 0)
	{
		m_vars.push_back(var);
		return;
	}
	auto it = m_vars.cbegin();
	while (it != m_vars.end() && var.GetName() > it->GetName())
	{
		it++;
	}
	m_vars.insert(it, var);
}
