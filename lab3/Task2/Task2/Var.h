#pragma once
#include <string>

class Var
{	
public:
	Var(std::string name);
	std::string GetName() const;
	double GetValue() const;
	void SetValue(double value);
private: 
	std::string m_name;
	double m_value = NAN;
};
