#include "Function.h"
#include <stack>

Function::Function
(
	std::string name,
	FunctionBody body
)
	: m_name(name)
	, m_body(body)
{}

std::string Function::GetName() const
{
	return m_name;
}

FunctionBody Function::GetBody() const
{
	FunctionBody body{};
	return body;
}

double CalcOperation(double leftOperand, double rightOperand, Operation operation)
{
	switch (operation)
	{
	case Operation::Addition:
		return leftOperand + rightOperand;
	case Operation::Subtraction:
		return leftOperand - rightOperand;
	case Operation::Multiplication:
		return leftOperand * rightOperand;
	case Operation::Division:
		return leftOperand / rightOperand;
	default:
		return NAN;
	}
}

double Function::GetValue() const
{
	Var leftOperand;
	Var rightOperand;
	std::stack<double> stack;
	for (auto& lexeme : m_body)
	{
		if (lexeme.IsOperation())
		{
			rightOperand.SetValue(stack.top());
			stack.pop();
			leftOperand.SetValue(stack.top());
			stack.pop();
			double value = CalcOperation(leftOperand.GetValue(), rightOperand.GetValue(), lexeme.GetOperation());
			stack.push(value);
		}
		else
		{
			stack.push(lexeme.GetVar().GetValue());
		}
	}

	return stack.top();
}





