#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle final : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
};

