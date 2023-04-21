#include "Memory.h"

void Memory::AddVar(Var& var)
{
	m_vars.push_back(var);
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
