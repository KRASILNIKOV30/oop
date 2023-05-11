#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment final : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_color;
};

