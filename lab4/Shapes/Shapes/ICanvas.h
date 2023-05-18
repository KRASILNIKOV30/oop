#pragma once
#include "Cpoint.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	// �������� ����������� ���������� (����������)
	virtual ~ICanvas() = default;
	virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
	virtual void FillRect(CPoint topLeft, double width, double height, uint32_t fillColor) = 0;
	//Render ������ ���� � ���������� ������ (����������)
};