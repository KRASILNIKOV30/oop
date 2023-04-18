#pragma once
#include <optional>
#include <string>

enum Operations
{
	Addition,
	Subtraction,
	Multiplication,
	Division
};

class Function
{
public:
	Function
	(
		std::string name,
		double leftOperand,
		std::optional<Operations> operation = std::nullopt,
		std::optional<double> rightOperand = std::nullopt
	);
	std::string GetName() const;

private:
	std::string m_name;
	double m_leftOperand;
};