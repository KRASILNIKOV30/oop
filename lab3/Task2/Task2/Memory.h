#pragma once
#include "Var.h"
#include <vector>
#include <optional>
#include <map>

using VarsMap = std::map<std::string, Var>;
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
	void InsertVar(Var& var);
};

