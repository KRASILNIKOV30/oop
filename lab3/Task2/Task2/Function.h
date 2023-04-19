#pragma once
#include "Var.h"
#include <optional>
#include <string>
#include <vector>
#include "Lexeme.h"

using FunctionBody = std::vector<Lexeme>;

class Function
{
public:
	Function
	(
		std::string name,
		FunctionBody body
	);
	std::string GetName() const;
	FunctionBody GetBody() const;
	double GetValue() const;

private:
	std::string m_name;
	FunctionBody m_body;
};