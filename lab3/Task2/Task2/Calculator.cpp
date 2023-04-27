#include "Calculator.h"
#include <algorithm>
#include <iterator>

VarsVector Calculator::GetVars() const
{
	return m_memory.GetVars();
}

FunctionsVector Calculator::GetFunctions() const
{
	return m_functions;
}

OptionalVar Calculator::FindVar(std::string name) const
{
	return m_memory.FindVar(name);
}

OptionalFunction Calculator::FindFunction(std::string name) const
{
	auto result = std::find_if(begin(m_functions), end(m_functions), [name](Function fn) { return fn.GetName() == name; });
	if (result == end(m_functions))
	{
		return std::nullopt;
	}

	return *result;
}

bool Calculator::IsFunction(std::string name) const
{
	return FindFunction(name).has_value();
}

bool Calculator::IsVar(std::string name) const
{
	return m_memory.FindVar(name).has_value();
}

bool Calculator::AddLexemes(std::vector<std::string>& lexemes, std::string name) const
{
	if (IsVar(name) || IsOperation(name))
	{
		lexemes.push_back(name);
		return true;
	}
	if (IsFunction(name))
	{
		Function function = FindFunction(name).value();
		std::vector<std::string> functionsLexemes = function.GetLexemes();
		for (auto& lexeme : functionsLexemes)
		{
			lexemes.push_back(lexeme);
		}
		return true;
	}
	return false;
}

bool Calculator::DefineVar(std::string name)
{
	m_memory.AddVar(name);
	return true;
}

bool Calculator::DefineFunction(std::string name, std::string leftOperandName)
{
	std::vector<std::string> lexemes{};
	if (!AddLexemes(lexemes, leftOperandName))
	{
		return false;
	}
	Function function(name, lexemes, m_memory);
	InsertFunction(function);
	return true;
}

bool Calculator::DefineFunction(
	std::string name,
	std::string leftOperandName, 
	std::string operation,
	std::string rightOperandName
)
{
	std::vector<std::string> lexemes{};
	AddLexemes(lexemes, leftOperandName);
	AddLexemes(lexemes, rightOperandName);
	AddLexemes(lexemes, operation);
	Function function(name, lexemes, m_memory);
	InsertFunction(function);
	return true;
}

void Calculator::InsertFunction(Function& fn)
{
	if (m_functions.size() == 0)
	{
		m_functions.push_back(fn);
		return;
	}
	auto it = m_functions.cbegin();
	while (it != m_functions.end() && fn.GetName() > it->GetName())
	{
		it++;
	}
	m_functions.insert(it, fn);
}

bool Calculator::ChangeVarValue(std::string varName, double value)
{
	return m_memory.ChangeVarValue(varName, value);
}
