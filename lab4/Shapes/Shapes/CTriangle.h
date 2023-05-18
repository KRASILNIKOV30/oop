#pragma once
#include "CSolidShape.h"
#include "CPoint.h"

class CTriangle final : public CSolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const final;
	double GetPerimeter() const final;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(ICanvas& canvas) const final;
	
private:
	std::string GetShapeInfo() const override;
	CPoint m_vertex1, m_vertex2, m_vertex3;
};

