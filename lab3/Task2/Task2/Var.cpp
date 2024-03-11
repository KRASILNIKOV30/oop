#include <compare>
#include "Var.h"

double Var::GetValue() const
{
	return m_value;
}

void Var::SetValue(double value)
{
	m_value = value;
}

Token Var::RegisterObserver(Observer& observer)
{
	while (!m_observers.try_emplace(++m_nextToken, observer).second)
		;

	return m_nextToken;
}

void Var::RemoveObserver(Token token)
{
	m_observers.erase(token);
}

void Var::NotifyObservers() const
{
	for (auto& [_, observer] : m_observers)
	{
		observer();
	}
}



