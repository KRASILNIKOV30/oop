#pragma once
#include "Shape.h"

class SolidShape : public Shape 
{
public:
	SolidShape(uint32_t fillColor, uint32_t outlineColor)
		: Shape(outlineColor)
		, m_fillColor(fillColor)
	{
	}
	uint32_t GetFillColor() const { return m_fillColor; }

private:
	uint32_t m_fillColor;
};