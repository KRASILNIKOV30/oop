#pragma once
#include <cstdint>
#include <string>

class IShape
{
public:
	virtual double GetArea() const;
	virtual double GetPerimeter() const;
	virtual std::string ToString() const;
	virtual uint32_t GetOutlineColor() const;
};