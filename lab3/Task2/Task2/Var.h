#pragma once
#include <string>

class Var
{	
public:
	explicit Var(std::string name);
	std::string GetName() const;
	double GetValue() const;
	void SetValue(double value);
	std::strong_ordering operator<=>(const Var& var) const;
private: 
	std::string m_name;
	double m_value = NAN;
};
