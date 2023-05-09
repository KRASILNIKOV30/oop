#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape
{
public:
	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;
	uint32_t GetOutlineColor() const;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_color;
};

