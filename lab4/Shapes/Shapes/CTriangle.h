#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;
	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	
private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
	uint32_t m_fillColor, m_outlineColor;
};

