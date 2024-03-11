#pragma once
#include <string>
#include <map>
#include "IObservable.h"

class Var: public IObservable
{	
public:
	// std::string GetName() const;
	double GetValue() const;
	void SetValue(double value);
	Token RegisterObserver(Observer& observer) override;
	void RemoveObserver(Token token) override;

private:
	void NotifyObservers() const override;

private: 
	double m_value = NAN;
	std::unordered_map<Token, Observer> m_observers;
	Token m_nextToken = 0;
};
