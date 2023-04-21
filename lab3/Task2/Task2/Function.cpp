#include "Function.h"
#include <stack>

Function::Function
(
	std::string name,
	std::vector<std::string> lexemes,
	Memory& memory
)
	: m_name(name)
	, m_lexemes(lexemes)
	, m_memory(memory)
{}

std::string Function::GetName() const
{
	return m_name;
}

std::vector<std::string> Function::GetLexemes() const
{
	return m_lexemes;
}

double CalcOperation(double leftOperand, double rightOperand, std::string operation)
{
	if (operation == "+")
	{
		return leftOperand + rightOperand;
	}
	if (operation == "-")
	{
		return leftOperand - rightOperand;
	}
	if (operation == "*")
	{
		return leftOperand * rightOperand;
	}
	if (operation == "/")
	{
		return leftOperand / rightOperand;
	}

	return NAN;
}

bool isOperation(std::string str)
{
	return str == "+" || str == "-" || str == "*" || str == "/";
}

double Function::GetValue() const
{
	double leftOperand;
	double rightOperand;
	std::stack<double> stack;
	for (auto & lexeme : m_lexemes)
	{
		if (isOperation(lexeme))
		{
			rightOperand = stack.top();
			stack.pop();
			leftOperand = stack.top();
			stack.pop();
			double value = CalcOperation(leftOperand, rightOperand, lexeme);
			stack.push(value);
		}
		else
		{
			auto var = m_memory.FindVar(lexeme);
			if (!var.has_value())
			{
				return NAN;
			}
			stack.push(var->GetValue());
		}
	}

	return stack.top();
}





