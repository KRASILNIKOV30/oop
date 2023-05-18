#pragma once
#include "CShape.h"
#include "CPoint.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color);
	double GetArea() const final;
	double GetPerimeter() const final;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const final;

private:
	std::string GetShapeInfo() const final;
	CPoint m_startPoint;
	CPoint m_endPoint;
};

