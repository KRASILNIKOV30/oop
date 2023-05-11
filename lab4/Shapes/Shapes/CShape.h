#pragma once
#include "IShape.h"
class CShape : public IShape
{
public:
	CShape(uint32_t outlineColor)
		:m_outlineColor(outlineColor)
	{}
	uint32_t GetOutlineColor() const override { return m_outlineColor; }
	//�� ������� ; ����� ���� ������, ������ ����������� ����������� � ����������� (����������)

private:
	uint32_t m_outlineColor;
};

