#pragma once
#include "Var.h"
#include <vector>
#include <optional>

using VarsVector = std::vector<std::reference_wrapper<Var>>;
using OptionalVar = std::optional<std::reference_wrapper<Var>>;

class Memory	
{
public:
	void AddVar(Var& var);
	OptionalVar FindVar(std::string name) const;
	VarsVector GetVars() const;
private:
	VarsVector m_vars;
};

