#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle final : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height, uint32_t fillColor, uint32_t outlineColor)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
		, m_fillColor(fillColor)
		, m_outlineColor(outlineColor)
	{}
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

