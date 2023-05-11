#pragma once
#include "ISolidShape.h"
class CSolidShape : public ISolidShape
{
public:
	CSolidShape(uint32_t fillColor, uint32_t outlineColor)
		: m_fillColor(fillColor)
		, m_outlineColor(outlineColor)
	{}
	uint32_t GetFillColor() const override { return m_fillColor; }
	uint32_t GetOutlineColor() const override { return m_outlineColor; }

private:
	uint32_t m_fillColor, m_outlineColor;
};

