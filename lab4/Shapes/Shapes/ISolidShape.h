#pragma once
#include "IShape.h"

class ISolidShape : public IShape 
{
public:
	ISolidShape(uint32_t fillColor, uint32_t outlineColor)
		: IShape(outlineColor)
		, m_fillColor(fillColor)
	{
	}
	uint32_t GetFillColor() const { return m_fillColor; }

private:
	uint32_t m_fillColor;
};