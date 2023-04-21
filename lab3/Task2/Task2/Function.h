#pragma once
#include "Var.h"
#include <optional>
#include <string>
#include <vector>
#include "Memory.h"

class Function
{
public:
	Function
	(
		std::string name,
		std::vector<std::string> lexemes,
		Memory& memory
	);
	std::string GetName() const;
	std::vector<std::string> GetLexemes() const;
	double GetValue() const;

private:
	std::string m_name;
	std::vector<std::string> m_lexemes;
	Memory& m_memory;
};