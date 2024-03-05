#include "PolishNotation.h"
#include <vector>
#include <stack>
#include <numeric>
#include <functional>

namespace
{
    using Argument = std::vector<double>;
    enum class Operation { Add, Sub, Mult, Div };
    struct Expression
    {
        Operation operation;
        Argument args = {};
    };
    using ExprStack = std::stack<Expression>;
}

Operation GetOperation(char ch)
{
    switch (ch)
    {
    case '+':
        return Operation::Add;
    case '-':
        return Operation::Sub;
    case '*':
        return Operation::Mult;
    case '/':
        return Operation::Div;
    }
}

double CalculateExpression(Expression const& expr)
{
    switch (expr.operation)
    {
    case Operation::Add:
        return std::reduce(expr.args.begin() + 1, expr.args.end(), expr.args[0], std::plus<double>());
    case Operation::Sub:
        return std::reduce(expr.args.begin() + 1, expr.args.end(), expr.args[0], std::minus<double>());
    case Operation::Mult:
        return std::reduce(expr.args.begin() + 1, expr.args.end(), expr.args[0], std::multiplies<double>());
    case Operation::Div:
        return std::reduce(expr.args.begin() + 1, expr.args.end(), expr.args[0], std::divides<double>());
    }
}

Expression ReadExpression(std::istream& input)
{
    char ch;
    input >> ch;
    Expression expr{ GetOperation(ch) };
    while (input >> ch)
    {
        input.unget();
        if (ch == ')' || ch == '(')
        { 
            return expr;
        }
        double arg;
        input >> arg;
        expr.args.push_back(arg);
    }
}

void CloseExpression(ExprStack& stack)
{
    if (stack.size() > 1)
    {
        double value = CalculateExpression(stack.top());
        stack.pop();
        stack.top().args.push_back(value);
    }
}

double CalculatePolish(std::istream& input)
{
    ExprStack stack;
    char ch;
    double value = 0;
    while (input >> ch)
    {
        switch (ch)
        {
        case '(':
        {
            stack.push(ReadExpression(input));
        }
        break;
        case ')':
        {
            CloseExpression(stack);
        }
        break;
        default:
        {
            CloseExpression(stack);
            input.unget();
            input >> value;
            stack.top().args.push_back(value);
        }
        }
    }
    
    return CalculateExpression(stack.top());
}
