#pragma once
#include <cstdint>
#include <string>

class IShape
{
public:
	IShape(uint32_t outlineColor)
		:m_outlineColor(outlineColor)
	{
	}
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	uint32_t GetOutlineColor() const { return m_outlineColor; }

private:
	uint32_t m_outlineColor;

};