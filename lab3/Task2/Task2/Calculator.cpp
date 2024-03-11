#include "Calculator.h"
#include "Common.h"
#include <iterator>

VarsMap Calculator::GetVars() const
{
	return m_memory->GetVars();
}

FunctionsVector Calculator::GetFunctions() const
{
	FunctionsVector result{};
	for (auto& item : m_functions)
	{
		result.push_back(item.second);
	}
	return result;
}

OptionalVar Calculator::FindVar(std::string const& name) const
{
	return m_memory->FindVar(name);
}

OptionalFunction Calculator::FindFunction(std::string const& name) const
{
	auto result = m_functions.find(name);
	if (result == end(m_functions))
	{
		return std::nullopt;
	}

	return result->second;
}

bool Calculator::IsFunction(std::string const& name) const
{
	return FindFunction(name).has_value();
}

bool Calculator::IsVar(std::string const& name) const
{
	return m_memory->FindVar(name).has_value();
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

bool Calculator::DefineVar(std::string const& name)
{
	if (IsIdentifierAlreadyInUse(name))
	{
		return false;
	}
	return m_memory->AddVar(name);
}

bool Calculator::DefineFunction(std::string const& name, std::string leftOperandName)
{
	if (IsIdentifierAlreadyInUse(name))
	{
		return false;
	}
	std::vector<std::string> lexemes{};
	if (!AddLexemes(lexemes, leftOperandName))
	{
		return false;
	}
	Function function(name, lexemes, m_memory);
	m_functions.insert({ function.GetName(), function });
	return true;
}

bool Calculator::DefineFunction(
	std::string const& name,
	std::string const& leftOperandName,
	std::string const& operation,
	std::string const& rightOperandName
)
{
	if (IsIdentifierAlreadyInUse(name))
	{
		return false;
	}
	std::vector<std::string> lexemes{};
	AddLexemes(lexemes, leftOperandName);
	AddLexemes(lexemes, rightOperandName);
	AddLexemes(lexemes, operation);
	Function function(name, lexemes, m_memory);
	m_functions.insert({ function.GetName(), function });
	return true;
}

bool Calculator::IsIdentifierAlreadyInUse(std::string const& name) const
{
	return FindFunction(name).has_value() || FindVar(name).has_value();
}

bool Calculator::ChangeVarValue(std::string const& varName, double value)
{
	return m_memory->ChangeVarValue(varName, value);
}
