#pragma once
#include "Var.h"
//лишний include (Исправлено)
#include <string>
#include <vector>
#include "Memory.h"
#include <memory>
#include <optional>

class Function
{
public:
	Function
	(
		std::string name,
		std::vector<std::string> lexemes,
		std::shared_ptr<Memory> memory
	);
	std::string GetName() const;
	std::vector<std::string> GetLexemes() const;
	double GetValue() const;
	//Избавиться от оператора присваивания (Исправлено)
private:
	std::string m_name;
	std::vector<std::string> m_lexemes;
	//Можно через указатель (Исправлено)
	std::shared_ptr<Memory> m_memory;
};