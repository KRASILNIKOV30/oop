#pragma once
#include "Var.h"
#include <optional>
#include <string>
#include <vector>
#include "Lexeme.h"

class Function
{
public:
	Function
	(
		std::string name,
		std::vector<Lexeme> lexemes
	);
	std::string GetName() const;
	std::vector<Lexeme> GetLexemes() const;
	double GetValue() const;

private:
	std::string m_name;
	std::vector<Lexeme> m_lexemes;
};