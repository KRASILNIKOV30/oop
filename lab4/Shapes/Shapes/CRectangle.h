#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string GetShapeInfo() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightTop() const;
	CPoint GetRightBottom() const;
	CPoint GetLeftBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) final;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
};

