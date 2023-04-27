#pragma once
#include "Var.h"
#include <vector>
#include <optional>

using VarsVector = std::vector<Var>;
using OptionalVar = std::optional<Var>;

class Memory	
{
public:
	bool AddVar(std::string name);
	bool ChangeVarValue(std::string varName, double value);
	OptionalVar FindVar(std::string name) const;
	VarsVector GetVars() const;
private:
	VarsVector m_vars;
	void DeleteVar(std::string name);
	void InsertVar(Var& var);
};

