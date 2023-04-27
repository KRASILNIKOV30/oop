#pragma once
#include "Var.h"
//лишний include
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
	Function& operator=(const Function&);//Избавиться
private:
	std::string m_name;
	std::vector<std::string> m_lexemes;
	//Можно через указатель
	Memory& m_memory;
};