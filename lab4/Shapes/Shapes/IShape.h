#pragma once
#include <cstdint>

class IShape
{
public:
	virtual double GetArea() const;
	virtual double GetPerimeter() const;
	virtual double ToString() const;
	virtual uint32_t GetOutlineColor() const;
};