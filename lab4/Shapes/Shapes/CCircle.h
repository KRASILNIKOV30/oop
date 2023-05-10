#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;
	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;
	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint center;
	double radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

