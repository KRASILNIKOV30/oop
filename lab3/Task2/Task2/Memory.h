#pragma once
#include "Var.h"
#include <optional>
#include <map>

using VarsMap = std::map<std::string, Var, std::less<std::string>>;
using OptionalVar = std::optional<Var>;

class Memory	
{
public:
	bool AddVar(std::string const& name);
	bool ChangeVarValue(std::string const& varName, double value);
	OptionalVar FindVar(std::string const& name) const;
	VarsMap GetVars() const;
private:
	VarsMap m_vars{};
	void DeleteVar(std::string const& name);
};

