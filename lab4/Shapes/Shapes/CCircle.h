#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CCircle final : public CSolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const final;

private:
	std::string GetShapeInfo() const override;
	CPoint m_center;
	double m_radius;
};

